package com.example.android;

import static com.example.android.MacAddressValidator.isValidMacAddress;

import android.content.Context;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.activity.EdgeToEdge;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;
import com.hoho.android.usbserial.driver.UsbSerialProber;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        // Find elements by id
        ToggleButton myToggle = findViewById(R.id.toggleButton);
        Button sendButton = findViewById(R.id.submitButton);
        EditText macAddressField = findViewById(R.id.macInput);
        EditText dataField = findViewById(R.id.dataInput);

        final int WRITE_WAIT_MILLIS = 2000;

        // Set an OnClickedListener
        sendButton.setOnClickListener(v -> {
            String macAddress = macAddressField.getText().toString();
            if (!isValidMacAddress(macAddress)) {
                Toast.makeText(MainActivity.this, "Mac address is invalid", Toast.LENGTH_SHORT).show();
                return;
            }
            String jsonData = dataField.getText().toString();

            if(!isValidJson(jsonData)){
                Toast.makeText(MainActivity.this, "JSON is invalid", Toast.LENGTH_SHORT).show();
                return;
            }

            // Initialize usb port
            UsbSerialPort port = getUsbSerialPort();
            if (port == null) return;
            String output = macAddress + jsonData;

            try {
                port.write(output.getBytes(), WRITE_WAIT_MILLIS);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            Toast.makeText(MainActivity.this, output, Toast.LENGTH_SHORT).show();
        });

        // Set an OnCheckedChangeListener
        myToggle.setOnCheckedChangeListener((buttonView, isChecked) -> {
            // Initialize usb port
            UsbSerialPort port = getUsbSerialPort();
            if (port == null) return;
            try {
                if (isChecked) {
                    port.write("ON\n".getBytes(), WRITE_WAIT_MILLIS);
                } else {
                    port.write("OFF\n".getBytes(), WRITE_WAIT_MILLIS);
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            // Add your logic here
            Toast.makeText(MainActivity.this, "Light toggled", Toast.LENGTH_SHORT).show();
        });
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }

    @Nullable
    private UsbSerialPort getUsbSerialPort() {
        UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
        List<UsbSerialDriver> availableDrivers = UsbSerialProber.getDefaultProber().findAllDrivers(manager);
        if (availableDrivers.isEmpty()) {
            Toast.makeText(MainActivity.this, "No USB device connected", Toast.LENGTH_SHORT).show();
            return null;
        }

        // Open a connection to the first available driver.
        UsbSerialDriver driver = availableDrivers.get(0);
        UsbDeviceConnection connection = manager.openDevice(driver.getDevice());
        if (connection == null) {
            return null;
        }

        UsbSerialPort port = driver.getPorts().get(0); // Most devices have just one port (port 0)
        try {
            port.open(connection);
            port.setParameters(115200, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return port;
    }

    private boolean isValidJson(String json) {
        try {
            new JSONObject(json);
        } catch (JSONException e) {
            return false;
        }
        return true;
    }
}