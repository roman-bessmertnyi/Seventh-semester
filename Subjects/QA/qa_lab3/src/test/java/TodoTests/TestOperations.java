package TodoTests;

import org.junit.Assert;
import org.openqa.selenium.WebElement;

public class TestOperations {
    Page page;

    public TestOperations(Page page) {
        this.page=page;
    }


    public void assertItemInputFocused(){
    }

    public void assertNewInputFocused(){
        WebElement activeElement = page.driver.switchTo().activeElement();
        Assert.assertTrue(page.waitForElement(page.getNewInputCss()).equals(activeElement));
    }

    public void assertNewInputBlurred(){
    }

    public void assertItemCount(int itemCount){
        Assert.assertTrue((itemCount == 0) ? page.waitForNoElement(page.getListCss()) :
                page.waitForListItemCount()==itemCount);
    }

    public void assertClearCompleteButtonText(){
    }

    public void assertClearCompleteButtonVisibility(){
    }

    public void assertMainSectionVisibility(boolean shouldBeVisible) {
        if (shouldBeVisible) Assert.assertFalse(page.waitForNoElement(page.getMainSectionCss()));
        else Assert.assertTrue(page.waitForNoElement(page.getMainSectionCss()));
    }

    public void assertFooterVisibility(boolean shouldBeVisible){
        if (shouldBeVisible) Assert.assertFalse(page.waitForNoElement(page.getFooterSectionCss()));
        else Assert.assertTrue(page.waitForNoElement(page.getFooterSectionCss()));
    }

    public void assertItemToggleIsHidden(){
    }

    public void assertItemLabelIsHidden(){
    }

    public void assertNewItemInputFieldText(){
    }

    public void assertItemText(){
    }

    public void assertItems(String[] items){
        for (int i=0; i < items.length; i++) {
            Assert.assertTrue(page.waitForTextContent(items[i], page.getListItems().get(i)));
        }
    }

    public void assertItemCountText(){
    }

    public void assertItemCompletedStates(){
    }

    public void assertFilterAtIndexIsSelected(){
    }

    public void assertCompleteAllCheckedStatus(){
    }
}