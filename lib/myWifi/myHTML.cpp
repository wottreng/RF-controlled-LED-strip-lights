/*
my HTML 

this is where all the html data is stored...

*/
#include <Arduino.h>
#include <string.h>
// custom libs
#include <myF.h>


//
#define myHTML_setup_html "<!DOCTYPE html>" \
"<html lang='en'>" \
"<head>" \
"<meta charset='UTF-8'>" \
"<title>Wifi Setup</title>" \
"</head>" \
"<style>" \
"body {" \
"position: relative;" \
"top: 0;" \
"left: 0;" \
"color: white;" \
"background-color: transparent;" \
"height: 100vh;" \
"width: 100vw;" \
"margin: 0;" \
"padding: 0;" \
"z-index: 0;" \
"}" \
".flexContainer {" \
"background-image: linear-gradient(180deg, #00008B, black);" \
"z-index: 1;" \
"position: relative;" \
"margin: 0;" \
"padding: 0;" \
"width: 100%;" \
"height: 100%;" \
"display: flex;" \
"text-align: center;" \
"align-items: center;" \
"align-content: center;" \
"flex-wrap: nowrap;" \
"flex-direction: column;" \
"overflow-y: scroll;" \
"font-weight: bold;" \
"}" \
".title {" \
"padding: 10px;" \
"font-size: x-large;" \
"}" \
".subTitle {" \
"padding: 5px;" \
"font-size: large;" \
"}" \
".subFlexBlock {" \
"z-index: 2;" \
"font-size: large;" \
"position: relative;" \
"left: 0;" \
"margin: 0;" \
"margin-bottom: 10px;" \
"padding: 10px;" \
"width: 100%;" \
"max-width: 300px;" \
"height: auto;" \
"display: flex;" \
"flex-direction: column;" \
"text-align: center;" \
"align-items: center;" \
"align-content: center;" \
"}" \
".greenBorder {" \
"background-color: black;" \
"color: white;" \
"width: 90%;" \
"border: #FAF0E6 solid 6px;" \
"border-radius: 20px;" \
"}" \
".whiteBorder {" \
"background-color: #818181;" \
"color: #18453B;" \
"width: 80%;" \
"border: #ffffff solid 6px;" \
"border-radius: 20px;" \
"}" \
".blackBorder {" \
"background-color: #18453B;" \
"color: white;" \
"width: 85%;" \
"border: #000000 solid 6px;" \
"border-radius: 20px;" \
"}" \
".textBlocks {" \
"font-size: large;" \
"text-align: center;" \
"align-content: center;" \
"align-items: center;" \
"padding: 2px;" \
"margin: 0;" \
"}" \
"button {" \
"margin: 0;" \
"font-size: large;" \
"padding: 5px 10px 5px 10px;" \
"color: #b4b4b4;" \
"background-color: black;" \
"border-radius: 10px;" \
"border: #18453B solid 4px;" \
"text-decoration: underline #b4b4b4;" \
"}" \
".greyText {" \
"color: #b4b4b4;" \
"}" \
"</style>" \
"<body>" \
"<div class='flexContainer'>" \
"<div class='title greyText'>LED Light Strip Controller</div>" \
"<div id='date'></div>" \
"<script type='text/JavaScript' defer>" \
"let a = new Date();" \
"let b = String(a).split(' GMT')[0];" \
"document.getElementById('date').innerHTML = `${b}`;" \
"//console.log(b);" \
"</script>" \
"<div class='subFlexBlock greenBorder'>" \
"<p class='textBlocks greyText'>STATUS</p>" \
"<p class='textBlocks'>current wifi AP SSID: &nbsp <b> REPLACE_WITH_wifi_ssid </b></p>" \
"</div>" \
"<div class='subFlexBlock greenBorder'>" \
"<p class='textBlocks greyText'>CONNECT TO WIFI</p>" \
"<p class='textBlocks'>Add a New Network</p>" \
"</br>" \
"<div style='display:flex;flex-wrap: wrap;flex-direction: row; justify-content: space-around;'>" \
"<form action='/input' method='POST'> Wifi ssid :<br>" \
"<input type='text' name='wifi SSID' value=''>" \
"<br> Wifi password:<br>" \
"<input type='password' name='password' value=''>" \
"<br><br>" \
"<input type='submit' value='Submit'>" \
"</form>" \
"</div>" \
"</div>" \
"</div>" \
"</body>" \
"</html>" 


//
String myHTML_return_setup_html(String ssid){
    String setuphtml = myHTML_setup_html;
    setuphtml.replace("REPLACE_WITH_wifi_ssid", ssid);
    return setuphtml;
}

// AP change response
#define ap_change_html "<meta http-equiv=\"refresh\" content=\"30; url='/'\" />" \
             "<body> trying to connect to new wifi connection </br> " \
             "if connection is successful you will be disconnected from soft AP</br>" \
             "please wait a minute then click below to go to main page</body>" \
             "<br/><p>click to go back to main page:&nbsp <a href=\"/\"><button style=\"display: block;\">AP Main Page</button></a>"

// not found
#define not_found_html "<meta http-equiv=\"refresh\" content=\"5; url='/'\" />" \
             "<body> not a know page for ESP server </br> you will be directed automaticly or click button below to be redirected to main page</br>" \
             "<br/><p>click to go back to main page:&nbsp <a href=\"/\"><button style=\"display: block;\">AP Main Page</button></a>"

// main page
#define main_page_html  "<!DOCTYPE html>" \
"<html lang='en'>" \
"<head>" \
"<meta charset='UTF-8'>" \
"<title>Light Control</title>" \
"<meta name='viewport' content='width=device-width, initial-scale=1'/>" \
"<meta http-equiv='refresh' content='300; url='/''/>" \
"</head>" \
"<style>" \
"body {" \
"position: relative;" \
"top: 0;" \
"left: 0;" \
"color: white;" \
"background-color: transparent;" \
"height: 100vh;" \
"width: 100vw;" \
"margin: 0;" \
"padding: 0;" \
"z-index: 0;" \
"}" \
".flexContainer {" \
"background-image: linear-gradient(180deg, #00008B, black);" \
"z-index: 1;" \
"position: relative;" \
"margin: 0;" \
"padding: 0;" \
"width: 100%;" \
"height: 100%;" \
"display: flex;" \
"text-align: center;" \
"align-items: center;" \
"align-content: center;" \
"flex-wrap: nowrap;" \
"flex-direction: column;" \
"overflow-y: scroll;" \
"font-weight: bold;" \
"}" \
".title {" \
"padding: 10px;" \
"font-size: x-large;" \
"}" \
".subTitle {" \
"padding: 5px;" \
"font-size: large;" \
"}" \
".subFlexBlock {" \
"z-index: 2;" \
"font-size: large;" \
"position: relative;" \
"left: 0;" \
"margin: 0;" \
"margin-bottom: 10px;" \
"padding: 10px;" \
"width: 100%;" \
"max-width: 300px;" \
"height: auto;" \
"display: flex;" \
"flex-direction: column;" \
"text-align: center;" \
"align-items: center;" \
"align-content: center;" \
"}" \
".greenBorder {" \
"background-color: black;" \
"color: white;" \
"width: 90%;" \
"border: #FAF0E6 solid 6px;" \
"border-radius: 20px;" \
"}" \
".whiteBorder {" \
"background-color: #818181;" \
"color: #18453B;" \
"width: 80%;" \
"border: #ffffff solid 6px;" \
"border-radius: 20px;" \
"}" \
".blackBorder {" \
"background-color: #18453B;" \
"color: white;" \
"width: 85%;" \
"border: #000000 solid 6px;" \
"border-radius: 20px;" \
"}" \
".textBlocks {" \
"font-size: large;" \
"text-align: center;" \
"align-content: center;" \
"align-items: center;" \
"padding: 2px;" \
"margin: 0;" \
"}" \
"button {" \
"margin: 0;" \
"font-size: large;" \
"padding: 5px 10px 5px 10px;" \
"color: #b4b4b4;" \
"background-color: black;" \
"border-radius: 10px;" \
"border: #18453B solid 4px;" \
"text-decoration: underline #b4b4b4;" \
"}" \
".greyText {" \
"color: #b4b4b4;" \
"}" \
"</style>" \
"<body>" \
"<div class='flexContainer'>" \
"<div class='title greyText'>LED Light Strip Controller</div>" \
"<div id='date'></div>" \
"<script type='text/JavaScript' defer>" \
"let a = new Date();" \
"let b = String(a).split(' GMT')[0];" \
"document.getElementById('date').innerHTML = `${b}`;" \
"//console.log(b);" \
"</script>" \
"<div class='subFlexBlock greenBorder'>" \
"<p class='textBlocks greyText'>STATUS</p>" \
"<p class='textBlocks'>Light Status: x_lighton_x</p>" \
"<p class='textBlocks'>Light Color: x_lightcolor_x</p>" \
"</div>" \
"<div class='subFlexBlock greenBorder'>" \
"<p class='textBlocks greyText'>LED COLOR</p>" \
"<p class='textBlocks'>Manual Switch Control:</p>" \
"</br>" \
"<div style='display:flex;flex-wrap: wrap;flex-direction: row; justify-content: space-around;'>" \
"<a href='changeColor?color=0'>" \
"<button style='display: block;'>WHITE</button>" \
"</a>" \
"<a href='changeColor?color=1'>" \
"<button style='display: block;'>RED</button>" \
"</a>" \
"<a href='changeColor?color=2'>" \
"<button style='display: block;'>GREEN</button>" \
"</a>" \
"<a href='changeColor?color=3'>" \
"<button style='display: block;'>BLUE</button>" \
"</a>" \
"<a href='changeColor?color=4'>" \
"<button style='display: block;'>ORANGE</button>" \
"</a>" \
"<a href='changeColor?color=5'>" \
"<button style='display: block;'>YELLOW</button>" \
"</a>" \
"<a href='changeColor?color=6'>" \
"<button style='display: block;'>BRIGHTER</button>" \
"</a>" \
"<a href='changeColor?color=7'>" \
"<button style='display: block;'>DARKER</button>" \
"</a>" \
"<a href='changeColor?color=8'>" \
"<button style='display: block;'>JUMP3</button>" \
"</a>" \
"<a href='changeColor?color=9'>" \
"<button style='display: block;'>JUMP7</button>" \
"</a>" \
"<a href='changeColor?color=10'>" \
"<button style='display: block;'>ON/OFF</button>" \
"</a>" \
"</div>" \
"</div>" \
"</br></br></br></br></br></br></br>" \
"<div class='subFlexBlock greenBorder'>" \
"Wifi Status:&nbsp <b>CON_STATUS</b></br>" \
"AP Name:&nbsp <b>REPLACE_WITH_AP</b></br>" \
"local IP:&nbsp<b>LOCAL_IP</b>" \
"</div>" \
"<div class='subFlexBlock whiteBorder'>" \
"<span class='textBlocks'>Change Wifi Access Point: </span><a href='/APsetup'>" \
"<button style='display: block;'>Wifi Setup</button>" \
"</a>" \
"</div>" \
"<p>Version x_VERSION_x</p>" \
"</div>" \
"</body>" \
"</html>" 

//
String myHTML_return_main_page_html(String version, String ssid, uint8_t connection_status, String local_ip, bool light_on, String light_color)
{
    String html_data = main_page_html;
    //
    if (light_on == 1){
        html_data.replace("x_lighton_x", "on");
    }else html_data.replace("x_lighton_x", "off");
    
    html_data.replace("x_lightcolor_x", light_color); // number of color choice
    html_data.replace("x_VERSION_x", version);
    // WL_IDLE_STATUS      = 0,WL_NO_SSID_AVAIL    = 1,WL_SCAN_COMPLETED   = 2,WL_CONNECTED        = 3,
    // WL_CONNECT_FAILED   = 4,WL_CONNECTION_LOST  = 5,WL_DISCONNECTED     = 6

    if (connection_status == 0) {
        html_data.replace("CON_STATUS", "Idle");
        html_data.replace("REPLACE_WITH_AP", ssid);
        html_data.replace("LOCAL_IP", local_ip);
    } else if (connection_status == 3) {
        html_data.replace("CON_STATUS", "Connected");
        html_data.replace("REPLACE_WITH_AP",ssid);
        html_data.replace("LOCAL_IP",local_ip);
    } else if (connection_status == 1) {
        html_data.replace("CON_STATUS", "Not Connected");
        html_data.replace("REPLACE_WITH_AP", ssid);
        html_data.replace("LOCAL_IP", "");
    } else {
        html_data.replace("CON_STATUS", "Error: " + String(connection_status));
        html_data.replace("REPLACE_WITH_AP", ssid);
        html_data.replace("LOCAL_IP", "");
    }

    return html_data;
}
