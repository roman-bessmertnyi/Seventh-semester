package appTests;

import app.ExceptionManager;
import app.IExceptionConfigReader;
import app.ILogServer;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.AdditionalMatchers;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;

import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.NotSerializableException;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.when;

@RunWith(MockitoJUnitRunner.class)
public class ExceptionCriticalityTests {
    @Mock
    IExceptionConfigReader exceptionConfigReaderMock;

    @Mock
    ILogServer logServerMock;

    @Test
    public void TestIsCritical_True() {
        when(exceptionConfigReaderMock.readIsCritical(any(IOException.class)))
                .thenReturn(true);

        Exception e = new IOException();
        ExceptionManager excMg = new ExceptionManager(exceptionConfigReaderMock, logServerMock);
        Assert.assertTrue(excMg.IsCritical(e));
    }

    @Test
    public void TestIsCriticalDerivered() {
        when(exceptionConfigReaderMock.readIsCritical(any(IOException.class)))
                .thenReturn(true);

        ExceptionManager excMg = new ExceptionManager(exceptionConfigReaderMock, logServerMock);
        Assert.assertTrue(excMg.IsCritical(new FileNotFoundException()));
        Assert.assertTrue(excMg.IsCritical(new EOFException()));
        Assert.assertTrue(excMg.IsCritical(new NotSerializableException()));
    }

    @Test
    public void TestIsCriticalDerivered_False() {
        when(exceptionConfigReaderMock.readIsCritical(AdditionalMatchers.not(any(IOException.class))))
                .thenReturn(false);

        ExceptionManager excMg = new ExceptionManager(exceptionConfigReaderMock, logServerMock);
        Assert.assertFalse(excMg.IsCritical(new NullPointerException()));
        Assert.assertFalse(excMg.IsCritical(new InterruptedException()));
        Assert.assertFalse(excMg.IsCritical(new IllegalArgumentException()));
    }
}
