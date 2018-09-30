import org.junit.Assert;
import org.junit.Test;

import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.NotSerializableException;

public class ExceptionHandlerTests {

    @Test
    public void TestAllBasicCriticalExceptions() {
        Exception e = new IOException();
        ExceptionManager excMg = new ExceptionManager();
        excMg.HandleException(e);
        Assert.assertEquals(1, excMg.CritExceptions);
        Assert.assertEquals(0, excMg.NonCritExceptions);
    }

    @Test
    public void TestDeriveredCriticalExceptions_True() {
        ExceptionManager excMg = new ExceptionManager();
        excMg.HandleException(new FileNotFoundException());
        excMg.HandleException(new EOFException());
        excMg.HandleException(new NotSerializableException());
        Assert.assertEquals(3, excMg.CritExceptions);
        Assert.assertEquals(0, excMg.NonCritExceptions);
    }

    @Test
    public void TestDeriveredCriticalExceptions_False() {
        ExceptionManager excMg = new ExceptionManager();
        excMg.HandleException(new NullPointerException());
        excMg.HandleException(new InterruptedException());
        excMg.HandleException(new IllegalArgumentException());
        Assert.assertEquals(0, excMg.CritExceptions);
        Assert.assertEquals(3, excMg.NonCritExceptions);
    }
}