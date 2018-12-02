package TodoTests;

import org.junit.Before;
import org.junit.Test;
import org.openqa.selenium.Keys;

public class Editing extends TestSetup{
    @Before
    public void beforeEach()
    {
        createStandardItems();
        page.doubleClickItemAtIndex(1);
    }

    @Test
    public void shouldSaveEditsOnEnter() throws Exception {
        page.editItemAtIndex(1, "buy some sausages" + Keys.ENTER);
        testOps.assertItems(new String[]{TODO_ITEM_ONE,"buy some sausages", TODO_ITEM_THREE});
    }

    @Test
    public void shouldRemoveTheItemIfAnEmptyTextStringWasEntered() throws Exception {
        page.editItemAtIndex(1, Keys.ENTER.toString());
        testOps.assertItems(new String[]{TODO_ITEM_ONE, TODO_ITEM_THREE});
    }
}
