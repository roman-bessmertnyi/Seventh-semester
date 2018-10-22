package TodoTests;

import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Action;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.util.List;

public class Page {
    WebDriver driver;
    WebDriverWait pageWaiter;



    public Page(WebDriver driver) {
        this.driver = driver;
        pageWaiter = new WebDriverWait(driver, 10);
    }

    public String removeText(){
        String removeText = "";
        for (int i=0;i<=50;i++){
            removeText += Keys.BACK_SPACE;
        }
        for (int i=0;i<=50;i++){
            removeText += Keys.DELETE;
        }
        return removeText;
    }

    public By getMainSectionCss(){
        return By.xpath("//section[contains(@class,'main')]");
    }

    public By getFooterSectionCss(){
        return By.xpath("//footer[contains(@class,'footer')]");
    }

    public By getNewInputCss(){
        return By.xpath("//input[contains(@class,'new-todo')]");
    }

    public By getListCss(){
        return By.xpath("//ul[contains(@class,'todo-list')]");
    }

    public By getListItemCss(){
        return By.xpath("//ul[contains(@class,'todo-list')]/li");
    }

    public List<WebElement> getListItems(){
        return driver.findElements(getListItemCss());
    }

    public boolean waitForTextContent(String text, WebElement element){
        return pageWaiter.until(ExpectedConditions.textToBePresentInElement(element, text));
    }

    public WebElement waitForElement(By elementSearcher) {
        return pageWaiter.until(ExpectedConditions.visibilityOfElementLocated(elementSearcher));
    }

    public boolean waitForNoElement(By elementSearcher) {
        return pageWaiter.until(ExpectedConditions.invisibilityOfElementLocated(elementSearcher));
    }

    public int waitForListItemCount() {
        pageWaiter.until(ExpectedConditions.visibilityOfElementLocated(getListCss()));
        List<WebElement> itemList = driver.findElements(getListItemCss());
        return itemList.size();
    }

    public void doubleClickItemAtIndex(int index){
        Actions actions = new Actions(driver);
        actions.doubleClick(getListItems().get(index));
        actions.build().perform();
    }

    public void editItemAtIndex(int index, String itemText){
        Actions actions = new Actions(driver);
        actions.moveToElement(getListItems().get(index));
        actions.doubleClick();
        actions.sendKeys(removeText() + itemText);
        actions.build().perform();
    }
}
