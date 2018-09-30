package app;

import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;

public class LogServer implements ILogServer {
    @Getter @Setter ArrayList<String> Log;

    @Override
    public boolean recieveMessage(String message)
    {
        try {
            Log.add(message);
            return true;
        }
        catch (Exception e) {
            return false;
        }
    }
}
