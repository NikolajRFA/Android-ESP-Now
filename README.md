<h2>Description</h2>
<p>
  The aim of this project is to enable Android to ESP communication utilizing ESP-Now.
  We've come up with a solution where an android app transmits data (serial) to an ESP32 dongle connected via USB-C.
  The data is then forwarded by the ESP32 dongle to other ESPs (ESP-Now).
</p>
<ul>Why did we develop the project?
  <li>This approach enables a reduction in the complexity of systems when compared to systems that utilize an ESP-Now message broker - as ESPs are accessible directly from the android interface. </li>
  <li>As no brokers are needed in these types of systems we don't need internet access - communication is available while offline.</li>
  <li>The approach is inherently mobile as the interface is an android smartphone.</li>
</ul>

<img src="https://github.com/user-attachments/assets/c8d914cb-187a-46cd-a0c9-72c98ed0d9b1" width="600">
