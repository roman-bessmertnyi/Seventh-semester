import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)

@Suite.SuiteClasses({
        ExceptionCriticalityTests.class ,ExceptionHandlerTests.class
})
public class ExceptionManagerTestSuite {
}
