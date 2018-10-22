package TodoTests;

import org.junit.Test;

public class NoTodos extends TestSetup {
    @Test
    public void shouldHideMainAndFooter() throws Exception {
        testOps.assertItemCount(0);
        testOps.assertMainSectionVisibility(false);
        testOps.assertFooterVisibility(false);
    }
}
