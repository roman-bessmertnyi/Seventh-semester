package appTests;

import app.ExceptionManager;
import app.IExceptionConfigReader;
import app.ILogServer;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.Spy;
import org.mockito.junit.MockitoJUnitRunner;

import java.io.IOException;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@RunWith(MockitoJUnitRunner.class)
public class ExceptionHandlerTests {
    @Mock
    IExceptionConfigReader exceptionConfigReaderMock;

    @Spy
    ILogServer logServerMock;

    @Test
    public void TestBasicCriticalException() {
        when(exceptionConfigReaderMock.readIsCritical(any(IOException.class)))
                .thenReturn(true);

        when(logServerMock.recieveMessage(anyString()))
                .thenReturn(true);

        Exception e = new NullPointerException();
        ExceptionManager excMg = new ExceptionManager(exceptionConfigReaderMock, logServerMock);
        excMg.HandleException(e);
        verify(logServerMock).recieveMessage(e.toString());
        Assert.assertEquals(0, excMg.getLogErrors());
        //Assert.assertTrue(logServerMock.recieveMessage("message"));
    }
}
