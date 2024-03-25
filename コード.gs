function doGet() {
  myHTML = HtmlService.createTemplateFromFile("GPS");
  return myHTML.evaluate();
}

function writeData(timeStamp,n,s,number,datanumber)
{
  let ss = SpreadsheetApp.getActiveSpreadsheet()
  let sheet = ss.getSheetByName('現在位置');
  let numberList = [[number,datanumber,timeStamp,n,s]];
  
  if(number <=9)
  {
    if(number <= 3){
      var sheet2 = SpreadsheetApp.openById('1NB7W7-KOPmu9fXzBerbaDsCtL8nwlephuUoZgyGxJ4E').getSheetByName('データ履歴');
    }else if(number <=6){
      var sheet2 = SpreadsheetApp.openById('1G0haJ40oaOTi8KvW8r7jR8n8s63ocVYvVjRbK2-Z9e0').getSheetByName('データ履歴');
    }else if(number <= 9){
      var sheet2 = SpreadsheetApp.openById('1j1NnH6fSFW4aM9DAtDaYQriGXClZX8JCR7YXJ_STe18').getSheetByName('データ履歴');
    }

    let range2 = sheet2.getRange(datanumber + 1,((number + 2) % 3) * 6 + 1,1,5);
    range2.setValues(numberList);
  }else{

  }

  let range = sheet.getRange(number + 1,1,1,5);
  range.setValues(numberList);
}
