import org.junit.Assert;
import org.junit.Test;

import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.NotSerializableException;

public class ExceptionCriticalityTests {
    @Test
    public void TestIsCritical_True() {
        Exception e = new IOException();
        ExceptionManager excMg = new ExceptionManager();
        Assert.assertTrue(excMg.IsCritical(e));
    }

    @Test
        public void TestIsCriticalDerivered_True() {
        ExceptionManager excMg = new ExceptionManager();
        Assert.assertTrue(excMg.IsCritical(new FileNotFoundException()));
        Assert.assertTrue(excMg.IsCritical(new EOFException()));
        Assert.assertTrue(excMg.IsCritical(new NotSerializableException()));
    }

    @Test
    public void TestIsCriticalDerivered_False() {
        ExceptionManager excMg = new ExceptionManager();
        Assert.assertFalse(excMg.IsCritical(new NullPointerException()));
        Assert.assertFalse(excMg.IsCritical(new InterruptedException()));
        Assert.assertFalse(excMg.IsCritical(new IllegalArgumentException()));
    }
}