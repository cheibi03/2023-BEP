function doGet() {
  myHTML = HtmlService.createTemplateFromFile("GPS");
  return myHTML.evaluate();
}

function writeData(timeStamp,n,s,number,datanumber)
{
  let ss = SpreadsheetApp.getActiveSpreadsheet()
  let sheet = ss.getSheetByName('現在位置');//''の中身を現在位置のみを表示させるシート名に変更
  let numberList = [[number,datanumber,timeStamp,n,s]];

  var sheet2 = ss.getSheetByName('データ履歴');//''の中身を位置情報を保存するシート名に変更

  let range2 = sheet2.getRange(datanumber + 1,((number - 1) * 6 + 1,1,5);
  range2.setValues(numberList);

  let range = sheet.getRange(number + 1,1,1,5);
  range.setValues(numberList);
}
