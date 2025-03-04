package com.example.android;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MacAddressValidator {
    // Regular expression for a valid MAC address
    private static final String MAC_ADDRESS_PATTERN = "^[0-9A-Fa-f]{2}(-[0-9A-Fa-f]{2}){5}$";
    private static final Pattern pattern = Pattern.compile(MAC_ADDRESS_PATTERN);

    public static boolean isValidMacAddress(String macAddress) {
        if (macAddress == null) {
            return false;
        }
        Matcher matcher = pattern.matcher(macAddress);
        return matcher.matches();
    }
}
