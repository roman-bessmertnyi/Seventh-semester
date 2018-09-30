import java.io.IOException;
import lombok.*;

public class ExceptionManager {
    @Setter @Getter int CritExceptions = 0;
    @Setter @Getter int NonCritExceptions = 0;


    public boolean IsCritical(Exception e)
    {
        if (e instanceof IOException)
        {
            return true;
        }
        else return false;
    }

    public void HandleException(Exception e)
    {
        if (IsCritical(e)) CritExceptions++;
        else NonCritExceptions++;
    }
}
