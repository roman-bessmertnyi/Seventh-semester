package app;

import lombok.Getter;
import lombok.Setter;

public class ExceptionManager {
    @Setter
    @Getter
    int CritExceptions;
    @Setter
    @Getter
    int NonCritExceptions;
    @Setter
    @Getter
    int LogErrors;

    IExceptionConfigReader exceptionConfigReader;

    ILogServer logServer;

    public ExceptionManager(IExceptionConfigReader exceptionConfigReader, ILogServer logServer) {
        CritExceptions = 0;
        NonCritExceptions = 0;
        this.exceptionConfigReader = exceptionConfigReader;
        this.logServer = logServer;
    }

    public boolean IsCritical(Exception e) {
        return exceptionConfigReader.readIsCritical(e);
    }

    public void HandleException(Exception e) {
        if (IsCritical(e)) {
            CritExceptions++;
            boolean LogSuccess = logServer.recieveMessage(e.toString());
            if (!LogSuccess) {
                LogErrors++;
            }
        } else NonCritExceptions++;
    }


}
