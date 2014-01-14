/* ----------------------------------------------------------------------------------------------------------------*/
/* ---------->>> global settings needed for thickbox <<<-----------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------------*/
*{padding: 0; margin: 0;}

/* ----------------------------------------------------------------------------------------------------------------*/
/* ---------->>> thickbox specific link and font settings <<<------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------------*/
#TB_window {
	font: 12px Arial, Helvetica, sans-serif;
	color: #333333;
}

#TB_secondLine {
	font: 10px Arial, Helvetica, sans-serif;
	color:#666666;
}
/*
#TB_window a:link {color: #666666;}
#TB_window a:visited {color: #666666;}
#TB_window a:hover {color: #000;}
#TB_window a:active {color: #666666;}
#TB_window a:focus{color: #666666;}
*/
/* ----------------------------------------------------------------------------------------------------------------*/
/* ---------->>> thickbox settings <<<-----------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------------*/
#TB_overlay {
	position: fixed;
	z-index:100;
	top: 0px;
	left: 0px;
	height:100%;
	width:100%;
}

.TB_overlayMacFFBGHack {background: url(macFFBgHack.png) repeat;}
.TB_overlayBG {
	background-color:#000;
	filter:alpha(opacity=75);
	-moz-opacity: 0.75;
	opacity: 0.75;
}

* html #TB_overlay { /* ie6 hack */
     position: absolute;
     height: expression(document.body.scrollHeight > document.body.offsetHeight ? document.body.scrollHeight : document.body.offsetHeight + 'px');
}

#TB_window {
	position: fixed;
	background: #ffffff;
	z-index: 102;
	color:#000000;
	display:none;
	border: 4px solid #525252;
	text-align:left;
	top:50%;
	left:50%;
}

* html #TB_window { /* ie6 hack */
position: absolute;
margin-top: expression(0 - parseInt(this.offsetHeight / 2) + (TBWindowMargin = document.documentElement && document.documentElement.scrollTop || document.body.scrollTop) + 'px');
}

#TB_window img#TB_Image {
	display:block;
	margin: 15px 0 0 15px;
	border-right: 1px solid #ccc;
	border-bottom: 1px solid #ccc;
	border-top: 1px solid #666;
	border-left: 1px solid #666;
}

#TB_caption{
	height:25px;
	padding:7px 30px 10px 25px;
	float:left;
}

#TB_closeWindow{
	height:25px;
	padding:11px 25px 10px 0;
	float:right;
}

#TB_closeAjaxWindow{
	padding:7px 10px 5px 0;
	margin-bottom:1px;
	text-align:right;
	float:right;
}

#TB_ajaxWindowTitle{
	float:left;
	padding:7px 0 5px 10px;
	margin-bottom:1px;
}

#TB_title{
	background-color:#e8e8e8;
	height:27px;
}

#TB_ajaxContent{
	clear:both;
	padding:2px 15px 15px 15px;
	overflow:auto;
	text-align:left;
	line-height:1.4em;
}

#TB_ajaxContent.TB_modal{
	padding:15px;
}

#TB_ajaxContent p{
	padding:5px 0px 5px 0px;
}

#TB_load{
	position: fixed;
	display:none;
	height:13px;
	width:208px;
	z-index:103;
	top: 50%;
	left: 50%;
	margin: -6px 0 0 -104px; /* -height/2 0 0 -width/2 */
}

* html #TB_load { /* ie6 hack */
position: absolute;
margin-top: expression(0 - parseInt(this.offsetHeight / 2) + (TBWindowMargin = document.documentElement && document.documentElement.scrollTop || document.body.scrollTop) + 'px');
}

#TB_HideSelect{
	z-index:99;
	position:fixed;
	top: 0;
	left: 0;
	background-color:#fff;
	border:none;
	filter:alpha(opacity=0);
	-moz-opacity: 0;
	opacity: 0;
	height:100%;
	width:100%;
}

* html #TB_HideSelect { /* ie6 hack */
     position: absolute;
     height: expression(document.body.scrollHeight > document.body.offsetHeight ? document.body.scrollHeight : document.body.offsetHeight + 'px');
}

#TB_iframeContent{
	clear:both;
	border:none;
	margin-bottom:-1px;
	margin-top:1px;
	_margin-bottom:1px;
}
.img-support {background-image: url(https://img.agoda.net/images/zh-tw/online_agent.jpg); }
/*-----Page------*/
* {margin:0;padding:0}
html,body{font:small Arial, Helvetica, sans-serif;color:#666;background-color:#eee}
body{overflow-y:scroll;*overflow-y:none}
table {	border-collapse: collapse;	border-spacing: 0}
/*----- Change Position of 3 Box : Guest, Customer ,Credit ------*/
a{font:normal small Arial, Helvetica,sans-serif;outline:none}
a:link,a:visited,a:active{color:#3F90F9}
a:hover{color:#00ADFF}
img,table{border:0}
img{vertical-align:middle}
/*----- form inputs-----*/
input, select { font-family: Arial,Helvetica,sans-serif }
select,input[type="text"],input[type="password"],.inputbg {
    border:1px solid #8D9AA3;
    background-color:#FFFEDF;
    font-size:13px;
}
select {
    height: 24px;
    padding:2px 2px 2px 0;
    margin:0;
    line-height: 24px
}
input[type=checkbox] {
    height: 16px;
    font-size: 13px;
}
br{clear:both;font-size:1px}
/*----- Utils -----*/
.middle{vertical-align:middle}
.bottom{vertical-align:bottom}
.floatleft{float:left}
.floatright{float:right}
.center{text-align:center}
.left{text-align:left}
.right{text-align:right}
.handcursor{cursor:pointer}
.absolute{position:absolute}
.relative {position:relative}
.block, .show { display: block }
.nooverflow { overflow:hidden }
.spadding{padding-top:3px}
.widthfull{width:100%}
.disabled {background:#eee;color:#999}
.placeholder {color:#999}
/* Hide only visually, but have it available for screenreaders: h5bp.com/v */
.visuallyhidden { border: 0; clip: rect(0 0 0 0); height: 1px; margin: -1px; overflow: hidden; padding: 0; position: absolute; width: 1px}
/* Extends the .visuallyhidden class to allow the element to be focusable when navigated to via the keyboard: h5bp.com/p */
.visuallyhidden.focusable:active, .visuallyhidden.focusable:focus { clip: auto; height: auto; margin: 0; overflow: visible; position: static; width: auto}
/* Hide visually and from screenreaders, but maintain layout */
.invisible { visibility: hidden}
/* Contain floats: h5bp.com/q */
.clearfix:before, .clearfix:after { content: ""; display: table}
.clearfix:after { clear: both}
.clearfix { *zoom: 1}
/*----- class enforcer------*/
.ui-blue-link {
    *font-size: small;
}
/*----- Sprite Booking Form ------*/
.sprite {
	background:url(https://img.agoda.net/images/default/bookingform_sprite_v10.png) no-repeat;
	border: none;
}
.ic-title-guestdetail {width:22px; height:23px; background-position: -330px -7px;vertical-align: top; margin-right:5px}
.ic-title-rewards {width:22px; height:23px; background-position: -357px -7px;vertical-align: top; margin-right:5px}
.ic-title-discount {width:22px; height:23px; background-position: -386px -7px;vertical-align: top; margin-right:5px}
.ic-title-booking {width:22px; height:23px; background-position: -303px -7px;vertical-align: top; margin-right:5px}
.ic-title-popup {width:16px; height:17px; background-position: -141px -8px;vertical-align: bottom; margin-right:5px}
.ic-title-ballpopup {width:94px; height:14px; background-position: -4px -58px; vertical-align:middle; margin-left:5px}
.ic-question {width:16px;height:14px;background-position: -263px -10px}
.ic-questionmark {background-position: -175px -78px;height: 20px; width: 19px}
.ic-goldtick {background-position: -152px -79px;height: 19px; width: 18px; vertical-align:bottom}
.ic-question-small {width:11px;height:10px;background-position: -248px -12px}
.ic-bullet-grey {width:13px;height:10px;background-position: -139px -78px}
.ic-PPP { 
    width: 18px;
    height: 18px;
    background-position: -310px -80px;
    margin-left:5px;
}
/*-----Main------*/
#wrapped{background-color:#fff;margin:0 auto;width:100%;/*width:expression(document.body.clientWidth > 1200? "1175px": "auto" )*/}
#wrapper{width:976px;margin:0 auto;max-width:976px;min-width:752px;padding:10px;background-color:#fff}
#wrapper td{vertical-align:top}
#box_right {
    color:#000;
    width:380px;
    padding-top:35px;
    padding-left: 5px;
    *padding-left: 0
}
#box_right.thankyoupage {
    padding-top: 0
}
#box_left{width:510px;overflow:hidden}
.box_leftborder{width: 576px}
.box_leftborder.fullw{width:100%}
.box_border{border:2px solid #999}
.width_datalist{width:100%}
/*---Submit Booking---*/
.box_submit{margin-top:15px}
.box_submit p{padding:5px 0;color:#000}
.box_submit p.center{padding-top:5px}
.box_submit a{font-weight:bold;color:#0973fa !important}
.box_submit a:hover{color:#00ADFF}
.box_submit input{margin-top:14px}
.box_submit #btnContinue{margin-top:14px; width:20%}
.box_submit img{margin-right:10px}
.box_assurances{border:1px #ddd solid;padding:5px; text-align:right;margin:10px 0 0 30px}
.box_assurances p,.box_assurances a{color:#9136cf !important;font-weight:normal}

/*----Header---*/
#header{height: 115px;background: url(https://img.agoda.net/images/default/bg_header_2.png) 0 72px repeat-x;}
#logowrapper{width:980px;margin:0 auto;}
#logowrapper a{width:160px;height:94px;text-indent:-9999px;display:block;float:left;background-position:0px -356px;}
#txtSmarter{display: inline-block;padding:10px 0 0 10px }
.rightlogo{float:right}
.livechat{margin-top:8px;cursor:pointer}
.img-support {display:block;width:214px;height:48px; background: url(https://img.agoda.net/images/en-us/online_agent.jpg) 0 0 no-repeat}
.vs{float:right}
.vs a{color:#000;text-decoration:none;font:bold 8px Tahoma}
/*--MenuHeader---*/
.menu_bullet{width:800px;margin:0 auto 30px auto;position:relative}
.menu_bullet button{width:12px;height:13px;border:0; *vertical-align:top}
.menu_bullet table{text-align:center;z-index:10;position:relative;margin:auto}
.menu_bullet span{margin-top:5px;display:block;color:#999;font-weight:bold}
.menu_bullet span.active{color:#007cd6 !important}

.bulletbg,.bulletbgover,button.bulletbgpass{
}
.bulletbg{background-position:-160px -10px !important}
.bulletbgover{background-position:-176px -10px !important}
.bulletbgpass{background-position:-192px -10px !important}
.nav_hotel,.nav_room,.nav_cutomer,.nav_billing{position:relative}
.linemenu{border-top:2px solid #ccc;position:absolute;margin-top:5px}
.nav_hotel,.nav_room,.nav_cutomer,.nav_billing,.nav_room p.linemenu,.nav_cutomer p.linemenu{width:200px}
.nav_hotel p.linemenu{margin-left:96px}
.nav_hotel p.linemenu,.nav_billing p.linemenu{width:106px}
.nav_hotel button,.nav_room button,.nav_cutomer button,.nav_billing button{z-index:100;position:relative}
/*---Nav 2011---*/
.menu_bullet span, .menu_bullet button, .menu_bullet p { cursor:default}
.menu_bullet span.able, .menu_bullet button.able { cursor:pointer}    
.menu_bullet .linemenu.i1,.menu_bullet .linemenu.i2{margin-left:130px!important}
.menu_bullet .linemenu { *margin-left: -125px !important}
.menu_bullet .linemenu.i1 { *margin-left: 10px !important}
.menu_bullet .linemenu.i2 { *margin-left: 0px !important}
/*-------Header Guest,Customer,Credit---------*/
.pspecer, .pspacer{padding-top:10px}
.texterror{line-height:25px}
.pbottomspecer, .pbottomspacer{padding-bottom:10px}
/*-------Table Customer,Credit-------*/
#box_guest table{width:100%}
select.number{width:45px; margin:0 5px}
.title{width:48px}
/*----- Special requests ----- */
#bkg_lLblSpecialRequest { cursor:pointer;}
#bkg_lLblSpecialRequest:focus { border:1px dotted #000 }
.ic-plusminus {width:13px;height:14px;padding-right: 4px;vertical-align: bottom;*font-size:9px;*padding-right: 0;*margin-right:4px}
.minus .ic-plusminus {background-position: -3px -99px}
.plus .ic-plusminus {background-position: -3px -80px}
.spc_request{
	border:solid 1px #acadaf;
	margin:6px 0 5px;
	width: 488px;
}
.spc_request div{
    padding:5px 8px 3px;
	vertical-align:top;
}
.spc_request td{padding:0 1px 5px 0}
.spc_request td input{border:0;background-color:transparent;float:left;margin:0px 5px 0 0}
.spc_request td label{display:block;overflow:hidden}
.spc_request .pillar3col {
    display:inline-block;
    width:150px;
    padding:0;
    /* inline star hack - ie6 and 7 can only see this */
    /* zoom and inline to enable inline-block in lte ie7 */
    *zoom:1;
    *display:inline;
}
.spc_request .pillar3col#divAirportTrans {
    width:162px;
}
.flight_detail{border:1px solid #8D9AA3; color:#666666;display:block;width:160px;resize:none;height:50px;overflow:hidden}
.spc_note{padding:0 5px 10px}

/*----Customer Details----*/
.name{display:block;font-size:11px;text-align:center;padding-bottom:5px}
.text{float:left;width:93%;color:#000}
.text a{color:#666}
.check input,input.check{border:0;background-color:#fff; margin-right:5px; vertical-align:bottom}
.ico_qstion{width:20px}
.ico_qstion .absolute,.box_childage .ico_qstion{z-index:10}
.bkg_condition .popup_body{width:460px}
.bkg_condition{display:block; margin: 0 20px 2px 0}
.bkg_freecan {color:#3F90F9;cursor:pointer;text-decoration:underline}
.bkg_freecan:hover{color:#00ADFF}
/*----CreditCard Details----*/
.cardtype select{width:40%;margin-right:3px}
.cardtype input{width:50%;margin-right:5px}
.cardtype ul{text-indent:-9999px;list-style:none;float:left;width:100%}
.cardtype li{height:20px;float:left;margin:0 1px 1px 0;background-image:url(https://img.agoda.net/images/default/bookingform_sprite_v10.png)}
.cardtype li.logoPaymentMethod1{background-position: -140px -37px;  width: 32px}
.cardtype li.logoPaymentMethod2{background-position: -175px -37px;  width: 30px}
.cardtype li.logoPaymentMethod3{background-position: -209px -37px;  width: 29px}
.cardtype li.logoPaymentMethod4{background-position: -241px -37px;  width: 32px}
.cardtype li.logoPaymentMethod5{background-position: -277px -37px;  width: 62px}
.cardtype li.logoPaymentMethod6{background-position: -343px -37px;  width: 31px}
.cardtype li.logoPaymentMethod7{background-position: -380px -37px;  width: 20px}
.cardtype li.logoPaymentMethod8{background-position: -405px -37px;  width: 23px}
.cardtype li.logoPaymentMethod9{background-position: -432px -37px;  width: 37px}
.cardtype li.logoPaymentMethod10 {background-position: -475px -37px;  width: 32px}
.cardtype li.logoPaymentMethod11 {background-position: -513px -37px;  width: 34px}
input.radio,.radio input{border:none;width:auto;height:auto;background-color:#fff}
.div_cont{border-top:2px solid #999;position:relative;text-align:center;width:100%}
.p_lightline{border-top:2px solid #ccc;height:60px;padding:0 !important}
.linkback{font-size:11px !important;color:#3F90F9;text-decoration:none;position:absolute;top:35%;left:15px}
.expirydate .popup_body{width:600px;left:-50px}
/*------Booking Summary Page------*/
.bg_booking { margin: 3px 0; padding: 5px 6px; background-color: #efefef; line-height: 20px; overflow: hidden}
.bg_booking, .bg_grandtotal { border: 1px solid #cdcdcd}
    .bg_booking.final { background-color: #dddddd}
.sum_period { overflow: hidden; clear: both}
.box_note { margin-bottom: 20px}
    .box_note strong { color: #c00; padding-right: 5px; font: bold 13px Arial,Helvetica,sans-serif; text-transform: capitalize}
.clear { clear: both}
.sum_period .absolute { z-index: 11}
.sum_period a.iconquestion {
	color: #0283DE;
	cursor: pointer;
    display: inline-block;
    font-family: Arial !important;
    font-size: 13px;
    position: relative;
    z-index: 200;   
}
    .sum_period a.iconquestion img { margin-left: -2px; padding-left: 2px}
.sum_period .popup_body { width: 390px}
.sum_period .popup_header_promotion p { margin-left: 10px; line-height: 13px}
.div_bestprice { margin: 12px 20px 20px 0; text-align: right}
    .div_bestprice .absolute { z-index: 12}
    .div_bestprice a { text-decoration: none; margin-right: 3px; *margin-left: 5px}
    .div_bestprice .popup_body { bottom: 35px}
    .div_bestprice .calloutDown { bottom: 9px}
#pnlTotalPrice.bg_booking { padding: 8px 6px; }
#pnlTotalPrice {
    line-height: 1.4em;
}
/*---Login Reward---*/
.box_signin table { width: 280px; margin:-15px 0 0 -5px}
.box_signin td { padding: 2px 5px}
.box_signin input.btn_loginsub { margin-top: 10px}
.box_signin a { color: #000}
ul.box_signin { list-style: disc; line-height: 18px; margin:0 0 10px 45px}
.box_signin li { padding: 2px 10px 2px 0; margin-left: 25px}
    .box_signin li a { font: 13px Arial,Helvetica,sans-serif; color:#3F90F9; }    
    .box_signin li a:hover { color:#00adff }  
.remem_id {  
    display: block;
    font-size: 13px;
}
.remem_id input { 
    width: 15px;
    height: 15px !important;
    margin: 8px 5px 0 0;
}
.remem_id label { vertical-align: bottom;}
.forgot {
    margin: 0;
    width: auto;
    padding: 8px 6px;
}
.forgot .green_roundbtn{padding:1px 10px !important}
    .forgot strong { margin-bottom: 20px; display: block}
    .forgot p { margin-bottom: 10px}
    .forgot ul { list-style: none}
    .forgot input[type="text"] { width: 170px}
    .forgot .headingtext strong {margin-bottom: 8px;}
.point { padding: 0 10px}
.point select { 
    margin: 0 0 16px 0;
    width: 330px;
}
.point input{
    font-size: 16px;
    font-weight: bold;
    text-align:center;  
    display:inline-block;
    width:auto !important;
    height:auto !important;
    padding: 6px 20px;                                
    *padding:2px 0;
    border: solid 3px #109fff !important;
    color: #fff;
    background: #109fff;
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#44b2ff', endColorstr='#006dbf');
    background: -webkit-gradient(linear, left top, left bottom, from(#44b2ff), to(#006dbf));
    background: -moz-linear-gradient(top,  #44b2ff,  #006dbf);
    -moz-border-radius: 6px; 
    -webkit-border-radius: 6px;
    border-radius: 6px;
    -moz-box-shadow: 2px 2px 3px #c0bec3; 
    -webkit-box-shadow: 2px 2px 3px #c0bec3; 
    box-shadow: 2px 2px 3px #c0bec3;
    cursor:pointer;
}
/*----Payment----*/
*.rtop *,.rbottom *{display:block;overflow: hidden}
.r1,.r2,.r3,.r4,.r5,.r6{height:1px;font-size:0}
.r7,.r8{height:2px; font-size:0}
.r1{background-color:#CDCDCD}
.r2,.r3,.r4,.r5,.r6,.r7,.r8{background-color:#fff}
.r4,.r5,.r6,.r7,.r8,.rcontent{border-left:1px solid #CDCDCD; border-right:1px solid #CDCDCD}
.r2,.r3{border-left:2px solid #CDCDCD; border-right:2px solid #CDCDCD}
.r1{margin:0 10px}.r2{margin:0 8px}.r3{margin:0 6px}.r4{margin:0 5px}.r5{margin:0 4px}.r6{margin:0 3px}.r7{margin:0 2px}.r8{margin:0 1px}
.er1,.er2,.er3,.erb3,.er4,.erb4,.er5,.erb5,.er6,.erb6,.er7,.erb7{display:block; overflow:hidden; font-size:0}
.er1,.er2,.er3,.er4,.er5,.er6,.erb3,.erb4,.erb5,.erb6,.erb7{height:1px}
.er3,.er4,.er5,.er6,.er7{border-left:1px solid #848484; border-right:1px solid #848484}
.erb3,.erb4,.erb5,.erb6,.erb7{background:#fff; border-left:1px solid #848484; border-right:1px solid #848484}
.er1{margin:0 8px}
.er2{margin:0 6px}
.er3,.erb3{margin:0 4px;border-width:0 3px}
.er4,.erb4{margin:0 3px;border-width:0 3px}
.er5,.erb5{margin:0 2px;border-width:0 3px}
.er6,.erb6{margin:0 2px;border-width:0 2px} 
.er7,.erb7{margin:0 1px;border-width:0 2px;height:2px}
.er1,.er2{background:#848484}
.er3{background:#d6d6d6}
.er4{background:#dedede}
.er5,.er6,.er7{background:#e6e6e6}
/*---MessageValidat---*/
.updatepro{position:fixed; width:300px; height:101px;left:50%;top:50%;margin-left:-150px;margin-top:-50px; z-index: 100001}
.modaltext{padding:5px 10px; display:block; background:#f7f7f7 url(https://img.agoda.net/images/default/bg_error.gif) repeat-x;text-align:center;height:75px}
.modaltext span{background:url(https://img.agoda.net/images/default/loading_popup.gif) no-repeat 50% 50px;display:block; font:bold small Arial, Helvetica, sans-serif}
.modaltext, .modaltext span{height:75px}
/*-----Thank Page-------*/
.thankspacer{padding:10px 20px 5px}
.thxrewards {
    -webkit-border-radius: 6px;
    -moz-border-radius: 6px;
    border-radius: 6px;
    background-color: #EEEEEE;
    border: 1px solid #F0F0F0;
    margin: 0px auto 25px !important;
    padding-top: 3px;
    width: 85%;
}
.bg_headerbox {
    /*background: url("https://img.agoda.net/images/default/icon_rewards.gif") no-repeat scroll 10px 2px #eee;*/
    border-bottom: 2px solid #FFFFFF;
    height: 24px;
    margin: 0 7px;
    padding: 3px 10px 2px 14px;
    text-align: left;
}
.bg_headerbox .ic-title-rewards {vertical-align:middle}
.thxrewards p {
    padding: 10px 20px;
    margin-bottom:0px;
}
.ballthx{background:#efefef;height:28px}
.ic-whitecircles{background-position: -415px 3px;width:40px;height:28px}
.box_thank p.xsmall{padding:0 10px 5px 15px}
.box_bookcompleted { text-align:center }
.box_bookcompleted .head_title {   
    padding: 15px 20px 0pt 15px; 
    overflow: hidden;
}
.box_bookcompleted h2 { margin-bottom:25px }
.box_bookcompleted p { margin-bottom:0px }
.box_bookcompleted p.mb20 { margin-bottom:20px }
.thk_btn_zone {
    text-align:center;
    margin:20px 0 10px;
}
.green_points {
    color: #1DAD58;
    font-weight:bold;
}
/*---Exception 2011---*/
#divErrorHeader, .res_header {
	display:block;
	line-height:1;
}
#divErrorHeader .wrap, .res_header .wrap {
	width:auto;
	display:inline;
	float:left;	
}
#panE1 h4 {font-size:small}
.listexception {margin:10px auto; text-align:left;width:400px}
#divErrorBody .mid_box {   
    border:#ccc 1px solid;
    margin:25px 120px 40px 160px;
    padding:20px 20px 25px 35px;
}
#divErrorBody .mid_box h2 {
    font-size:18px;
    margin-bottom:16px;
}
#divErrorBody .mid_box br {line-height: 0.1; content: " "} 
#divErrorBody .mid_box ul {margin-left:15px;list-style:none}
#divErrorBody .mid_box ul li {
    margin-bottom:8px;
    padding-left:0;
}
#divErrorBody .mid_box li .ic-bullet-grey {
    margin-left:-15px; 
    *display:inline; 
    *zoom:1; 
    *vertical-align:middle; 
    *font-size:8px
}
#divErrorBody .mid_box ul li div {
    margin-left:10px;
    *zoom:1
}
#divErrorBody .mid_box ul li ul {list-style:disc inside; margin-top:6px}
#divErrorBody .mid_box ul li ul li {margin-bottom:0}
:root *> #divErrorBody .mid_box ul li ul li>span{vertical-align:top} /*not ie6-8*/
#divErrorBody .btnwrapper {
    text-align:center;
    margin:25px 0px
}
#divErrorBody a.blue_roundbtn {
    display:inline-block;
    float:none;
}
/*---Duplication---*/
.divDuplicate {
    padding:20px 25px 10px;
    border: 2px solid #CDCDCD;
}
.divDuplicate p { margin-bottom:10px}
.divDuplicate .optionwrapper {
    margin:8px;
}
.divDuplicate .btnwrapper {
    text-align:center;
    margin:25px 0px;
}
.divDuplicate input[type="radio"]{
    margin-bottom: 12px;
    margin-right: 5px;
}
.img-diffBrowse{
    background-position: -4px -35px;
    width:110px;
    height:16px
}
#box_diffBrowsing {
    display: inline-block;
    text-align: center;
    font-weight: bold;
    border: 1px solid #ccc;
    padding: 24px 0 0;
    margin: 150px 150px 250px;
    -webkit-box-shadow: 0px 0px 6px 0px rgba(0,0,0,0.45);
    box-shadow: 0px 0px 6px 0px rgba(0,0,0,0.45);
    -webkit-border-radius: 12px; 
          border-radius: 12px;
}
#box_diffBrowsing .textContent {
    padding: 0 24px;
    line-height: 1.4em;
}
#box_diffBrowsing .textContent p { margin-bottom: 20px }
#box_diffBrowsing .textContent a { font-weight: bold }
#box_diffBrowsing .img-diffBrowse { margin:0 12px 8px 0 }
/*-----Payment Thank Page-------*/
.box_payment{width:70%;margin:0 auto;text-align:center;padding-bottom:10px}
/*---Payment Pending---*/
.box_payment h2.bluesmall { margin: 15px 0 35px}
.box_payment h3.red {margin: 10px 0 25px}
/*--Round Corner Box--*/
*.btop *{display:block;overflow: hidden}
.b1,.b2,.b3{height:1px; font-size:0}
.b4{height:2px; font-size:0}
.b1,.b2,.b3,.b4{background-color:#efefef}
.b1{margin:0 5px}
.b2{margin:0 3px}
.b3{margin:0 2px}
.b4{margin:0 1px}
.tabmenu{background-color:#efefef;display:block;padding:2px 30px 2px 20px}
.tabmenu h1{font:bold medium Arial, Helvetica, sans-serif;padding-right:7px;display:inline-block;*display:inline;*zoom:1} 
.tabmenu .ic-whitecircles {background-position: -415px 1px;height:17px}
/*----Font Styles----*/
.bluebold{font-weight:bold;color:#2371D5;font-size:medium}
.bluesmall{color:#1275ED}
.blackbold{
    color:#000;
    font:bold 14px Arial, Helvetica, sans-serif
}
.blacklarge {
    color: #000;
    font: bold 16px Arial,Helvetica,sans-serif
}
.blacktext, a.blacktext { color:#000 }
.redbold{color:#c00;font-weight:bold}
.red{color:#c00}
.purpletext { color:#9436D4 }
.greentext { color:#20B35D }
.bluetext { color: #3F90F9 }
.xsmall,.xsmall a{font-size:11px}
.xsmallgreen{color:#1dad58; font:11px Arial, Helvetica, sans-serif}
.text-white {color:#fff}
.text-bold {font-weight: bold}
.text-12px { font-size: 12px }
/*----Button----*/	
.btn_white{background-color:#fff;cursor:pointer;font:bold 11px Arial,Helvetica,sans-serif;height:20px;color:#000;border-top:1px solid #ddd;border-left:1px solid #ddd;border-right:2px solid #898989;border-bottom:2px solid #898989}
.btn_loginsub {
	color:#fff;
	padding:0px 4px;
	height:29px !important;
	text-decoration:none;
	border:1px solid #96c8df;
	font:bold 14px Arial,Helvetica,sans-serif;
	background:#96c8df url(https://img.agoda.net/images/default/blue_btn.gif) repeat-x 0 -2px;
	cursor:pointer;
}
.btn_back {
	background-color:#eee;
	color:#000;
	height:29px;
	width:98px;
	padding:0 10px;
	text-decoration:none;
	background:#bbb url(https://img.agoda.net/images/default/gray_btn.gif) repeat-x 0 -2px;
	font:bold 14px Arial,Helvetica,sans-serif;
	border-top:1px solid #b4b4b4;
	border-right:2px solid #656565;
	border-bottom:2px solid #656565;
	border-left:1px solid #b4b4b4;
	cursor:pointer;
}
/*-----Footer------*/
#footer, .footer{width:100%;clear:both;text-align:center;padding:20px 0 10px}
#footer a, .footer a{font:small Arial, Helvetica, sans-serif;color:#666}
#footer a:hover, .footer a:hover{color:#9FA0A4}
#footer p, .footer p{margin-top:10px; clear:both}
#footer input.blue_roundbtn, .footer input.blue_roundbtn{ margin-left:15px; margin-bottom:10px}
.footer table{width:auto;margin:0 auto}
/*-----Window Popup-----*/
#divBpg { background-color:#fff;border-collapse:collapse;color:#000;width:700px }
.contentpopup{margin:10px 0;height:180px;overflow:auto;border:2px solid gray;padding:10px; text-align:left !important}
.contentpopup ul{padding-left: 50px; line-height: 120%; list-style-type: decimal}
.contentpopup p{margin:10px 0}
.popheading{font-size:medium;font-weight:bold;height:23px;color:#000;padding:5px 10px;background:#e6e6e6 /*url(https://img.agoda.net/images/default/ballpopup.gif) no-repeat 63px 7px*/; text-align:left !important}
.popheading .txtwrap {padding-top:3px}
.popdiv input{background-color:#fff;font-weight:bold;cursor:pointer;border-right:1px outset #29303b;border-bottom:1px outset #29303b;padding:3px 5px; border:1px solid #8D9AA3;font-size:11px}
.popdiv a {
	text-decoration:underline;
	font-size:12px;
	cursor:pointer;
}
.popheading input{float:right}
.popbody{padding:10px 20px}
.popbody p{padding-bottom:10px}
.popfooter{padding:10px;text-align:center}
.cms_securitycode{
    background:url(https://img.agoda.net/images/default/creditcard_verification.png) no-repeat 53px 75px;
    height:265px;
}
.yellow_popup {
	background-color: #FFF9E7;
    border: 2px solid #FEBA02;
    color: #444444;
    display: none;
    margin-top: 8px;
    padding: 10px;
    position: absolute !important;
    width: 360px;
    z-index: 200;
}
/*---------New PopUp MultiCurrency---------*/
.xxsmallgrey{color:#666; font:10px Arial, Helvetica, sans-serif}
.xsmallgrey{color:#666; font:11px Arial, Helvetica, sans-serif}
.roompro{color:#9436D4;font-size:12px}
.show{display:block}
.hide{display:none}
.flightcomment{
	font-size:11px;  
	clear:both;
	margin-top:5px;
}
.ic-comment{
	background-position: -282px -9px;
	height: 15px;
	width: 14px;
	*margin-right:3px;
}
/*--New--*/
.btn_blue{
	font:bold 18px Arial, Helvetica, sans-serif;
	cursor:pointer;
	color:#fff;
	border:1px solid #96c8df;
	padding:5px 7px;
	background:#96c8df url(https://img.agoda.net/images/default/blue_btn.gif) repeat-x 0 -2px;
}
/*Payment in Process*/
.imgload{background:url(https://img.agoda.net/images/default/loading_popup.gif) no-repeat; width:105px; height:20px}
.specer_payment{margin-top:15px}
.paymentspacer{padding:30px 20px 20px}

/*--News CSS-*/
.expirydate{padding-right:20px}
.blue_roundbtn {
    background: #109fff url(https://img.agoda.net/images/default/blue_btn.gif) repeat;
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#44b2ff', endColorstr='#006dbf');
    background: -webkit-gradient(linear, left top, left bottom, from(#44b2ff), to(#006dbf));
    background: -moz-linear-gradient(top,  #44b2ff,  #006dbf);
    border: solid 3px #109fff;
    -moz-border-radius: 7px; 
    -webkit-border-radius: 7px;
    border-radius: 7px;
    -moz-box-shadow: 2px 2px 3px #c0bec3; 
    -webkit-box-shadow: 2px 2px 3px #c0bec3; 
    box-shadow: 2px 2px 3px #c0bec3;
    color: #fff;
    cursor:pointer;
    font:bold 14px Arial, Helvetica, sans-serif;
    padding:0 10px;
    height:30px !important;
    text-align:center;	 
}
/* Thank you Page */
a.blue_roundbtn {
    background: #109fff url(https://img.agoda.net/images/default/blue_btn.gif) repeat-x;
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#44b2ff', endColorstr='#006dbf');
	background: -webkit-gradient(linear, left top, left bottom, from(#44b2ff), to(#006dbf));
    background: -moz-linear-gradient(top,  #44b2ff,  #006dbf);
	color:#fff !important;
	font:bold 14px Arial,Helvetica,sans-serif !important;
	text-decoration:none;
	margin-left:15px;
	padding: 0 16px 0 !important;
	line-height:24px !important;
	display:block;
	float:left;
	height:auto!important
}

.grey_roundbtn {
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#f9f9f9', endColorstr='#dddddd');
    background: -webkit-gradient(linear, left top, left bottom, from(#f9f9f9), to(#ddd));
    background: -moz-linear-gradient(top,  #f9f9f9,  #ddd);
    border: solid 1px #ccc;
    color: #666;
    cursor:pointer;
    padding:4px 8px;
    -moz-border-radius: 4px; 
    -webkit-border-radius: 4px;
    border-radius: 4px;
    -moz-box-shadow: 1px 1px 2px #DDD; 
    -webkit-box-shadow: 1px 1px 2px #DDD; 
    box-shadow: 1px 1px 2px #DDD;
    text-align:center;
    font-size: 11px;
    margin-top:-8px;
    margin-bottom: 8px;
    display: block;
    float:left;
}
.grey_roundbtn:hover {                                
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#fdfdfd', endColorstr='#d9d9d9');
    background: -webkit-gradient(linear, left top, left bottom, from(#fdfdfd), to(#d9d9d9));
    background: -moz-linear-gradient(top,  #fdfdfd,  #d9d9d9);
    border: solid 1px #aaa;
}

/* Booking Form - October 2011 */
#navMenu, #footer {
	width:976px;
}
#main {
    width:900px;
    margin:0 35px;
}   
.divErr {
	display:none;
	padding: 5px 0px 0px 10px;
}
/* Lead Guest */
.bkg_divInputRow {
	/*width: 98.9%; */
    width:auto;
	margin-left: 0px;
	overflow: hidden;
	display:block;
	clear:both;
	*cursor:default;
}
.bkg_divInputRow input, .forgot input[type=text] {
    height: 22px;
}
.bkg_divInputRow input[type=checkbox] {
    height: 16px;
}
.bkg_divInputCol {
	float:left;
    width:auto;
    margin-right: 30px;
    padding:0 0 12px 0;
}
#rowContact .bkg_divInputCol { *padding-bottom: 0 }
.bkg_divInputCol.wauto { width:auto }
.bkg_lblInput {
	display:block;
	margin-bottom:3px;
}
.bkg_divPayment_marginL { margin-left:17px }
.bkg_divPayment_marginR { margin-right:17px }
.pnlextrabed {
    margin-top:16px;
}
.bkg_pnlAdditionalnotes {
	padding: 0 0 8px 3px;
}
.border_content span.blackbold {
	margin-bottom:5px;
	display:block;
}
.cards_default2 {
    margin: 21px 0 0 2px;
    width:auto;
    float: left;
}
.ui-ddlAge {width:95px}
/* ------ BE3 and bookingdotcom bkdc------- */
#box_bkdcnote {
	padding: 5px;
	border: 2px solid #CDCDCD;
	width:auto;
}
#box_bkdcnote .notetext {
	width:272px;
	float: left;
}
#box_bkdcnote .notetext.wauto {	width:auto}
#box_bkdcnote .price {float:right;}
#bkdc_credithint { padding: 0px 0 10px 0 }
/* taken from bookingform html */
.rbh1,.rbh2,.rbh3,.rbh4{height:1px; font-size:0}
.rbh5,.rbh6{height:2px;font-size:0}
.rbh1{background-color:#CDCDCD}
.rbh4,.rbh5,.rbh6,.border_content{border-left:1px solid #CDCDCD;border-right:1px solid #CDCDCD;*zoom:1}
.rbh2,.rbh3{border-left:2px solid #CDCDCD;border-right:2px solid #CDCDCD}
.rbh2{background-color:#eee}
.rbh3{background-color:#EDEDED}
.rbh4{background-color:#F3F3F3}
.rbh5{background-color:#fdfdfd}
.rbh6{background-color:#fefefe} 
.rbh1{margin:0 8px} 
.rbh2{margin:0 6px}
.rbh3{margin:0 4px}
.rbh4{margin:0 3px}
.rbh5{margin:0 2px}
.rbh6{margin:0 1px}
.box_leftborder,.box_border,.div_cont,#box_guest strong.header{border:0}
.head_title {
    background:#F0F0F0 url(https://img.agoda.net/images/default/bg_tthome.png) repeat-x 0 0;
    border-bottom:1px solid #CDCDCD;
    color:#000000;
    padding:0 0 0 10px !important;
	overflow:hidden;
	margin-bottom:10px;
	font-family: Arial, Helvetica, sans-serif
}
#box_guest strong, #box_contact strong, #box_rewards strong{padding:0 0 5px}    
#box_guest span, #box_contact span{font-size:large !important}
.p_lightline{border-top-width:1px;height:50px}
a.btn_close{
    background-color: #DADADA;
    border: 1px solid #C9C9C9;
    color: #3A3A3A;
    display: block;
    font-weight:bold;
    height: 14px;
    line-height: 12px;
    position: absolute;
    right: 0;
    text-align: center;
    text-decoration: none;
    top: 0;
    width: 14px;
}
.green_roundbtn{
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#1ec767', endColorstr='#1b9e56');
    background: -webkit-gradient(linear, left top, left bottom, from(#1ec767), to(#1b9e56));
    background: -moz-linear-gradient(top,  #1ec767,  #1b9e56);
    background-color: #20b35d;
    border: solid 3px #33cc75;
    color: #fff;
    cursor:pointer;
    font:bold 14px Arial, Helvetica, sans-serif;
    padding:0 10px;
    -moz-border-radius: 7px; 
    -webkit-border-radius: 7px;
    border-radius: 7px;
    text-align:center;	
    display:inline-block 
}
.green_roundbtn:focus,
.green_roundbtn:hover {
    border-color: #109050;
}
.box_signin{padding:0 20px 0 10px}
.box_signin input.green_roundbtn{height:30px;padding:0 20px;margin:5px 0 5px 15px}
.rewardsLogin{margin-bottom:10px}
.rewardsLoginLabel{width:95px}
#divRewardsLogin { padding:8px 6px 4px }
#divRewardsLoginOn { padding:8px 6px }
#divRewardsLoginOn .inputtext{width:170px;margin-bottom:2px}
#divRewardsLoginOn .hint{font-style:oblique}
.border_content .content{padding-left:15px;padding-right:5px}
#divRewardsLogin .widthredeem{width:240px;float:left;display:inline-block;padding-top:3px}
#divRewardsLogin input{height:auto;white-space: normal;*width:105px;*white-space:nowrap}
#box_rewards .head_title{
    overflow:hidden;
	margin-bottom:0px;
    border-bottom:1px solid #CDCDCD !important
}
/*------- Rewards 2013 -------*/
#bkg_divRewards {
    padding-bottom: 0;
    margin-bottom: 15px;
    padding:0 0 4px;
    background: #f9f9f9;
    border: 1px solid #cdcdcd;
}
.rewardsformwrapper {
    border:1px solid #CDCDCD;
    background: #fff;
    border-radius: 6px;
    padding: 10px;
}
#bkg_divRewards #divRewardsLogin .headingtext { margin-bottom: 3px }
#divRewardsLogin_txt { width: 250px }
#bkg_divRewards .headingtext {
    font-size: 16px;
    margin-bottom: 10px;
}
#divRewardsLogin .wrapper {
    margin-right: 2px;
    height: auto;
    width:115px;
    *width:110px;
}
#divRewardsLogin .green_roundbtn  {
    font-size:20px;
    padding: 4px 6px;
}
#divRewardsLoginOn .rewardsformwrapper {
    margin-bottom: 8px;
    padding: 24px 16px;
}
#divRewardsLoginOn .formpadding {
    display: inline-block;
    width: 270px;
    padding: 0 0 12px 0;
    *padding-bottom: 0;
}
#divRewardsLoginOn .green_roundbtn {
    font-size:20px;
    padding: 6px 20px;
    height:auto;
}
#divRewardsLoginOn .labeltext {
    text-align: left;
    margin-bottom: 5px;
}
#divRewardsLoginOn input.inputtext {
    width: 100%;
    height: 22px;
}
.spacereward {
    margin-top:30px;
    text-align:left;
}
.spacereward a {
    color:#3F90F9;
    text-decoration: underline;
    font-size:11px
}
.spacereward a:hover { color:#00ADFF }                          
#divRedemption, #divChangepwd, #divForgot {                                
    padding:8px 6px !important;
}
/*----- Header 2013 -----*/
#divHeadTitle {
    font: normal 20px Arial, Helvetica, sans-serif;
    height: 30px;
}
/*----- Hotel n Room details 2013 -----*/
#tblHotelDes .hoteldetails-table {width:490px}
#tblHotelDes .hoteldetails-title { padding-bottom: 6px }
#tblHotelDes strong { padding: 0 16px 0 12px; display:inline-block; }
#tblHotelDes .hoteldetails-txt,
#tblHotelDes .hoteldetails-txt-label { padding: 0 0 5px; }
#tblHotelDes .hoteldetails-txt-label { width:100px; }
#tblRoomDes .roomdetails-txt { padding: 0 5px 0 12px;*width:380px/*avoid roomInfo expand when text too long ie6-7*/}
#tblRoomDes ul{
    padding:0;
    margin:0 0 0 16px;
    list-style: disc outside;
}
#tblRoomDes li { padding: 1px 0 }
#tblRoomDetail .roomtitle { padding-bottom: 8px }
#tblRoomDetail .bottom {vertical-align:bottom}
#tblRoomDetail .roomtitle .blacklarge {
    font-weight: normal;
    font-size: 13px;
    float: left;
    line-height: 20px;
}
#tblRoomDetail .pnlmouseoverBookCond {
    float: right;
    padding-right: 17px;
}
#tblRoomDetail .pnlmouseoverBookCond .popup_body {
    width: 425px;
    bottom: auto;
    top: 29px;
}
#tblTYHotelDetails .hoteldetails-image-wrapper {
    margin: 5px 0 0 5px;
}
#tblTYHotelDetails .hoteldetails-hotelname {
    padding-bottom:2px;
}
#tblTYHotelDetails .hoteldetails-txt-label {
    width: 100px;
}
#tblTYHotelDetails .hoteldetails-txt,
#tblTYHotelDetails .hoteldetails-txt-label {
    padding-bottom: 2px;
}
#tblTYHotelDetails .starrating {
    margin-top: 2px;
}
/*----- Star rating -----*/
.stars0{display:none}
.stars0_5,.stars1,.stars1_5,.stars2,.stars2_5,.stars3,.stars3_5,.stars4,.stars4_5,.stars5{    
    background-position: -235px -80px;
    border:0;height:13px;width:62px;
    display:inline-block;
    *display:inline;
    *zoom:1;

    vertical-align: top;
    margin: 3px 0 0 5px;
}
.stars0_5{width:6px}
.stars1{width:11px}
.stars1_5{width:18px}
.stars2{width:24px}
.stars2_5{width:31px}
.stars3{width:37px}
.stars3_5{width:44px}
.stars4{width:50px}
.stars4_5{width:57px}
.iconwrapper {
    display: inline-block;
    vertical-align: top;
    position:relative;
}
/*----- Continue button 2013 -----*/
#divContBtn {
    padding-top: 20px;
    padding-bottom: 8px;
    text-align:center;
}
#divContBtn .blue_roundbtn {
    font-size: 20px;
    height: auto !important;
    padding:10px 24px;
    *padding:6px 0;
}
#divContBtn .blue_roundbtn:focus,
#divContBtn .blue_roundbtn:hover {
    border-color: #1971EF;
}
.blue_roundbtn_wrapper {
    text-align:right;
    margin: 16px 12px 4px 0;
}
.blue_roundbtn_wrapper .blue_roundbtn {
    font-size: 20px;
    height: auto !important;
    padding: 8px 20px;
    *padding-left:0;
    *padding-right:0
}
.blue_roundbtn_wrapper .blue_roundbtn:focus, .blue_roundbtn_wrapper .blue_roundbtn:hover {
    border-color: #1971EF;
}
/*----- end Continue button 2013 -----*/
#box_bookingDetails .blackbold {
	line-height: 20px;
}
.head_title strong.header {
	padding:0 0 5px 0px;
    font-size:large;
}
.head_title strong.header.noicon {
	padding:0 0 5px 0px;
}
.popup_body{
    width: 350px;   
    color: #000;
    border: 2px solid #a0a0a0; 
    background:#fff url(https://img.agoda.net/images/default/mouse_overbg.gif) repeat-x;
    font-size: 12px;
    line-height: normal;
    text-decoration:none;
    z-index:100;
    -moz-border-radius: 15px;
    -webkit-border-radius: 15px;
    border-radius: 15px;
    -moz-box-shadow: 5px 5px 5px #a0a0a0;
    -webkit-box-shadow: 5px 5px 5px #a0a0a0;
    box-shadow: 5px 5px 5px #a0a0a0;
    position:absolute;
    right:-35px; 
    bottom:29px;
    padding-bottom:8px;
    cursor:default;
}  
.popup_body_left {
    right:auto;
    left:-50px !important;
}
.popup_header_promotion {
    background: -moz-linear-gradient(top, #fff, #f0f0f0);
    background: -webkit-gradient(linear,left top,left bottom,color-stop(0, #fff),color-stop(1, #f0f0f0)); 
    /* Saf4+, Chrome */ 
    background-image: url()\9;
    /*background-color:#f0f0f0 \9; */
    background-repeat:no-repeat;
    background-position: 0 6px;
    -moz-border-radius: 15px 15px 0 0;
    -webkit-border-radius: 15px 15px 0 0;
    border-radius: 15px 15px 0 0;
    padding:0 0 1px 0 !important;
    height:auto !important;
    color:#000 !important;
    font-weight:bold !important; 
    text-align:left;
}
.popup_header_promotion p{
    padding:8px 0 5px 3px !important;
    margin-bottom:0 !important;
    margin-left:10px;
}           
.popup_content_promotion{
    left: 2px; 
    top: 40px; 
    overflow:hidden;
    line-height:160%;
    text-align:left;
    padding:5px 20px 5px 18px;
}           
.calloutDown {
    bottom: 3px;
    height: 0;
    width: 0;
    border-color: #a0a0a0 transparent transparent transparent;
    /*border-color: #f00 transparent transparent transparent;*/
    border-style: solid;
    border-width: 14px;
    z-index: 102;
    right:-8px;
    position:absolute;
    margin:0;
}
.calloutDown2 {
    position: relative;
    left: -15px;
    top: -15px;
    height: 0;
    width: 0;
    border-color: #fff transparent transparent transparent;
    border-style: solid;
    border-width: 11px;
    z-index: 101;
} 
.calloutLeft {         
    height: 0;
    width: 0;
    border-right: 15px solid #A0A0A0;
    border-top: 15px dotted transparent;
    border-bottom: 15px dotted transparent;
    left: 0px;
    top: 0px;
    margin-left: 20px;
    margin-top: -15px;
    z-index: 102;
}
.calloutLeft2{
    position: relative;
    left: 0px;
    top: -20px;
    height: 0;
    width: 0;
    border-right: 13px solid #fff;
    border-top: 13px dotted transparent;
    border-bottom: 13px dotted transparent;
    z-index: 101;
}
.calloutUp {
    top: 3px;
    height: 0;
    width: 0;
    border-color: transparent transparent #a0a0a0 transparent;
    border-style: solid;
    border-width: 14px;
    z-index: 102;
    left:-8px;
    position:absolute;
    margin:0;
}
.calloutUp2 {
    position: relative;
    right: 15px;
    bottom: 11px;
    height: 0;
    width: 0;
    border-color: transparent transparent #fff transparent;
    border-style: solid;
    border-width: 13px;
    z-index: 101;
}        
.iconquestion{
    position:relative;
    cursor:pointer;
    z-index:200;                    
    font-family:Arial !important;
    display:inline-block;
}
div.bkg_rightdivs {
	margin-bottom:20px;
}
/*----- Booking Details -----*/
.bkgdt_marginb { margin-bottom:3px }
.bkgdt_margint { margin-top:16px }
#box_bookingDetails .head_title { margin-bottom:0 }

/* ----- urgency message --------*/
#divUrgencyMsg {
    margin: 0 0 5px 0;
    padding: 5px 6px;
    background: #093;
    border: 1px solid #CDCDCD
}
/*------ popups -----*/
#bkg_divCVCNo .ico_qstion{
	z-index:11; /* CVC above rightdivs*/
    margin: -19px 0 0 111px;
    _margin-left: 106px;
}
#bkg_divCVCNo .ico_qstion.withValidateOffset {
    margin-left:130px;
}
#bkg_divCountryIssueBank .ico_qstion {
    margin: -19px 0 0 224px;
    _margin-left: 217px;
    z-index: 11;
}
#bkg_divCountryIssueBank .ico_qstion.withValidateOffset {
    margin-left: 248px;
    _margin-left: 238px;
}
#bkg_divWhichBank .ico_qstion {
    margin: -19px 0 0 224px;
    _margin-left: 217px;
    z-index: 12;
}
#bkg_divWhichBank .ico_qstion.withValidateOffset {
    margin-left: 248px;
    _margin-left: 238px;
}
.pnlmouseoverBookCond .ico_qstion {
	display: inline-block;
    z-index: 10;
    margin: 3px 0 0 3px;
    *margin: 1px 0 0 3px;
    *zoom:1;
    *display:inline;
}
.pnlmouseoverTaxFee .ico_qstion_wrapper {
    display: inline-block;
    width: 18px;
    height: 12px;
    *display:inline;
    *zoom:1;
}
.pnlmouseoverTaxFee .ico_qstion {
	display: inline-block;
    z-index:10;
    width:16px;
    margin: 0 0 0 3px;
    *zoom:1;
    *display:inline;
}
.pnlmouseoverAgeofChild .ico_qstion {
	z-index:10;
    margin: -19px 0 0 92px;
}	
.pnlmouseoverAgeofChild .ico_qstion.withValidateOffset {
    margin-left: 116px;
}              
.div_bestprice .ico_qstion {
	margin:-1px 0 0 0;
	z-index:10;
	margin-left:-3px\9;
	*margin-top:-2px;
}
#divNeverShare .ico_qstion {
	z-index:10;
}
#divNeverShare .border_content_text { padding-right:5px}
.priceincludes {
	color:#686367;
}
.bookingcond {
	color:#0283DE;
	text-decoration:underline;
	cursor: pointer;
}    
.xsmalltext {
	font-size:x-small;
	line-height: 20px;
}
.rmdtl_firstrow td {
	padding-top:14px;
}
#bkg_divBookingDetails .bkgdt_width td {	    
	padding-right:5px;
	/* :last-child for ie6-7 */
	*padding-right:expression(this.nextSibling==null?'0':'inherit');
}
#bkg_divBookingDetails .bkgdt_width td:last-child{	    
	padding-right:0;
}
#bookingDetail .table-hoteldetails-inner td, #bookingDetail .table-hoteldetails-inner td .blackbold {
    line-height: 20px;
}
/*---New Content Popup--*/
.curvebox{
    -webkit-border-radius: 8px;
    -moz-border-radius:8px;
    border-radius: 8px;
    border: 1px solid #cecece;
    height: 358px;
    .height:395px;
    background-color: #fff;
    padding: 16px;
    overflow: auto;
    .font-size:12px
}
.curvebox h5{color: #000000;font-weight: bold;margin-bottom: 4px; font-size:13px}
.curvebox h6{font-style: italic;font-weight: normal;margin-top: 8px; font-size:13px}
.curvebox p{margin-bottom:15px}
.curvebox ul{list-style: none;}
.bullet {
    color: #999999;
    display: inline-block;
    font-size: 32px;
    margin-right:5px;
    margin-top: -9px;
    vertical-align:top
}
.popup_footer{ text-align:right;padding-top:10px;}
.popup_footer .bestprice:hover{ color:#0283DE}
.popup_footer .ic-goldtick{background-position: -209px -10px;.background-position: -209px -6px;.margin-right:5px;height: 14px;vertical-align: bottom;width: 15px;}
/*Align hotel rate on each row/column BKGsummary ie6-7*/
.bookingdetails .bkgdt_col1{*width:73%}
.bookingdetails .bkgdt_col2{*width:80px}
.trFinalPriceHint td, .bksum-includes td{ width:350px\9; width:50px\0/}/*fixTdColspanIE*/

.rmdtl_paddingright{
	padding-right:5px;
}
#footerDetail td {
	vertical-align:middle;
}
.bkgdt_col2 {
	width:34px;
	text-align:left;	    
}
.bkgdt_col3 {
	text-align:right;
	width:60px;
}
.bestprice {
    font-family: "Arial Rounded MT Bold","Arial Rounded MT", Arial, Helvetica, sans-serif;
    font-weight: normal;
    font-size: 13px;
    color: #0283df;
    -webkit-text-shadow: 0 1px 1px #fff;
    text-shadow: 0 1px 1px #fff;
    text-decoration: none;
    /*margin-left:25px*/
}
.bestprice:hover{ color:#00ADFF}

.border_content_text{
	padding-top:10px;
}    
table.bkgdt_width{
    width:100%;
}
.box_members {
    display: block;
    position: relative;
    padding-top: 20px;
}
/*.box_members a{
    color:#000;
}*/
.box_members a.btn_close {
    line-height: 14px;
    font-weight: bold;
    top: 5px;
    right: 3px;
    _right:8px;
    color:#666;
    z-index:10;
}
.box_members a.btn_logout {
    
    display: block;
    text-align:right;
    margin-bottom:6px;
    z-index:10;
    font-size:11px;
}
#bkg_divBooking td.middle {
    vertical-align:middle;
}
ul.checkboxlist {
    padding-left: 0;
    margin-left: 0;
}

ul.checkboxlist li {
    list-style:none;
    margin-bottom:6px;
   /* height:18px;*/
}

ul.checkboxlist input{
    vertical-align:middle;
    *margin: 0 -3px;
   /* margin:-3px 5px 0 0;*/
}
/*thickbox override default padding*/
#TB_ajaxContent.TB_modal {
    padding: 0px !important;
    /* override background 
    background-color: #000000 ;
    opacity: 0.75 ;*/
}
#TB_ajaxContent .rtop, #TB_ajaxContent .rbottom {
    /* override background 
    background-color: #000000 ;
    opacity: 0.75 ;*/
}
#TB_ajaxContent {
    padding: 0px !important;    /* disable TB default padding */
    height:auto !important; /* auto resize popup box hack */
}
/*
#TB_ajaxContent p {
    padding: 0 !important;
}
*/
#TB_ajaxContent #continuepopup p {
    padding: 5px !important;
}
#TB_ajaxContent .contentpopup{
    padding: 10px !important;
}
#TB_window 
{
    border:0px !important;
}
/* ----- submit please wait popup -----*/
#pnlContinue2Popup {
	/*background: #000;
	opacity:0.75;*/
}
#continuepopup {
	border:2px #848484 solid;
}
/* ----- redirect popup ------ */
#divRedirect {
	background-color: #FFFFFF;
    padding: 25px;
    width: 580px;
}
#divRedirect .container {
	border: 1px solid #9B9B9B;
    padding: 15px 25px 20px;
}
#btnRdrCancel {
	margin-right: 23px;
    padding: 0 5px !important;
    width: 62px;
}
#btnRdrOk {
	 width: 82px;
}

/* ----- 2011 submit booking ----- */
.filled {
	background-color: rgb(190, 225, 245) !important;
}
.inline-block {
    display:inline-block;
    *zoom:1;
    *display:inline;
}
.display-table-cell {display:table-cell}
.display-table-row {display:table-row}
/* --- Validation error return --- */
.errtext {
    font-style:normal;
    color:#e00;
    line-height:20px;
}
.errtext ul { list-style:none }
div.errtext ul{ list-style:disc inside }
/* --- Update panel issue bank --- */
.upibwrapper .cardtype ul {width:55%}
.upibwrapper .divcvc .ico_qstion{
	/*margin:-17px 0 0 79px;*/z-index:11; /* CVC above rightdivs*/
	margin: 2px 0 0 74px;
}
.upibwrapper .divcountryissue .ico_qstion{
	margin: 2px 0 0 152px;
	z-index:10;
}
.divwhichbank .ico_qstion{
	z-index:12; /* WhichBank above CVC*/
	margin: 2px 0 0 154px;
}	
.upibwrapper .payment_submit {
    margin: 0 0 10px 24px;
    overflow: hidden;
}
.upibwrapper .texterror {
    color: #FF0000;
    line-height: 22px;
}
.upibwrapper .divcvc .popup_body {
    left:30px;
    bottom:-120px;
    width:600px;
}
.msgconfirm p {
    padding-bottom:15px;
}
.survey_question {
    color: #000000; display: block; margin-bottom: 8px;margin-top: 10px;
}
.curvebox_AB1400 {
    -webkit-border-radius: 8px;
    -moz-border-radius: 8px;
    border-radius: 8px;
    -webkit-background-clip: padding-box;
    -moz-background-clip: padding;
    background-clip: padding-box;
    border: none;
    background-color: #F4F4F4;
    padding: 8px 12px 18px;
}
.curvebox_AB1400 .curvebox_title {
    margin: 4px 0 12px;
    font-size: 22px;
    font-weight: normal;
    color: #333;
}
.curvebox_AB1400 .contentwrapper {
    background: none;
    border: none;
    -webkit-border-radius: 5px;
        -moz-border-radius: 5px;
            border-radius: 5px;
    color: #666;
    text-align:center;
}
.curvebox_AB1400 .tborder {border-top:1px solid #ddd; margin-top:13px }
.curvebox_AB1400 .paymentoptions {
    background: #fff;
    display:block;
    padding:16px;
    cursor:pointer;    
    border: 1px solid #CECECE;
    -webkit-border-radius: 5px;
    -moz-border-radius: 5px;
    border-radius: 5px;
    font-size:48px;
    text-decoration:none;
}
.curvebox_AB1400 .paymentoptions:hover {background:#eee}
.curvebox_AB1400 .paymentoptions * {cursor:pointer}
.curvebox_AB1400 .paymentoptions .currtext {
    font-size:48px;
    display:block;
    line-height: 40px;
    margin-top: 4px;
    margin-left:20px;
    text-decoration:none;
}       
.curvebox_AB1400 .currsprite {
    background: url("https://img.agoda.net/images/default/CurrFlags_v3.png") no-repeat;
    width:110px;
    height:65px;
    vertical-align:middle;
    vertical-align:text-bottom;
    margin-left:24px;  
    background-position: 0 70px; /* fallback */            
        -webkit-box-shadow: 0px 0px 1px 0px rgba(0,0,0,0.4);
            -moz-box-shadow: 0px 0px 1px 0px rgba(0,0,0,0.4);
                box-shadow: 0px 0px 1px 0px rgba(0,0,0,0.4);
    border:1px solid #fff;
    border:1px solid #ddd\9;
    *border:1px solid #ddd;
}
#curr_AED.currsprite {background-position: 0 0}
#curr_ARS.currsprite {background-position: 0 -70px}
#curr_AUD.currsprite {background-position: 0 -140px}
#curr_BRL.currsprite {background-position: 0 -210px}
#curr_CAD.currsprite {background-position: 0 -280px}
#curr_CHF.currsprite {background-position: 0 -350px; width:65px;margin:0 22px 0 47px}
#curr_CNY.currsprite {background-position: 0 -420px}
#curr_CZK.currsprite {background-position: 0 -490px}
#curr_DKK.currsprite {background-position: 0 -560px}
#curr_EUR.currsprite {background-position: 0 -630px}
#curr_FJD.currsprite {background-position: 0 -700px}
#curr_GBP.currsprite {background-position: 0 -770px}
#curr_HKD.currsprite {background-position: 0 -840px}
#curr_HUF.currsprite {background-position: 0 -910px}
#curr_IDR.currsprite {background-position: 0 -980px}
#curr_ILS.currsprite {background-position: 0 -1050px}
#curr_INR.currsprite {background-position: 0 -1120px}
#curr_JOD.currsprite {background-position: 0 -1190px}
#curr_JPY.currsprite {background-position: 0 -1260px}
#curr_KZT.currsprite {background-position: 0 -1330px}
#curr_MXN.currsprite {background-position: 0 -1400px}
#curr_MYR.currsprite {background-position: 0 -1470px}
#curr_NGN.currsprite {background-position: 0 -1540px}
#curr_NOK.currsprite {background-position: 0 -1610px}
#curr_NZD.currsprite {background-position: 0 -1680px}
#curr_OMR.currsprite {background-position: 0 -1750px}
#curr_PHP.currsprite {background-position: 0 -1820px}
#curr_PKR.currsprite {background-position: 0 -1890px}
#curr_PLN.currsprite {background-position: 0 -1960px}
#curr_QAR.currsprite {background-position: 0 -2030px}
#curr_RON.currsprite {background-position: 0 -2100px}
#curr_RUB.currsprite {background-position: 0 -2170px}
#curr_SAR.currsprite {background-position: 0 -2240px}
#curr_SEK.currsprite {background-position: 0 -2310px}
#curr_SGD.currsprite {background-position: 0 -2380px}
#curr_THB.currsprite {background-position: 0 -2450px}
#curr_TRY.currsprite {background-position: 0 -2520px}
#curr_TWD.currsprite {background-position: 0 -2590px}
#curr_UAH.currsprite {background-position: 0 -2660px}
#curr_USD.currsprite {background-position: 0 -2730px}
#curr_VND.currsprite {background-position: 0 -2800px}
#curr_KRW.currsprite {background-position: 0 -2870px}
#curr_XPF.currsprite {background-position: 0 -2940px}
#curr_CFP.currsprite {background-position: 0 -2940px}
#curr_ZAR.currsprite {background-position: 0 -3010px}
        
@media only screen and (min-device-width: 768px) and (max-device-width: 1024px), only screen and (max-device-width: 480px){
	#TB_window{top:40%}
	.paymentoptions input{background-color:#FCF9AE;border:1px solid #cdcdcd}
	.curvebox_AB1400 .currsprite {    
        -webkit-box-shadow: 0px 0px 1px 2px rgba(0,0,0,0.2);
            -moz-box-shadow: 0px 0px 1px 2px rgba(0,0,0,0.2);
                box-shadow: 0px 0px 1px 2px rgba(0,0,0,0.2);
    }
}

.blue_roundbtn_disabled {
    background-color: #cccccc;
    background-image: -webkit-gradient(linear, left top, left bottom, from(#cccccc), to(#999999)); /* Safari 4+, Chrome */
    background-image: -webkit-linear-gradient(top, #cccccc, #999999); /* Chrome 10+, Safari 5.1+, iOS 5+ */
    background-image: -moz-linear-gradient(top, #cccccc, #999999); /* Firefox 3.6-15 */
    background-image: -o-linear-gradient(top, #cccccc, #999999); /* Opera 11.10+ */
    background-image: linear-gradient(to bottom, #cccccc, #999999); /* Firefox 16+ */
    filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#cccccc', endColorstr='#999999');
    border: solid 3px #999999;
    cursor: default;
    padding: 0 10px;
    height: 30px !important;
    -webkit-border-radius: 7px;
    border-radius: 7px;
    -moz-background-clip: padding;
    -webkit-background-clip: padding-box;
    background-clip: padding-box;
    -webkit-box-shadow: 3px 3px 5px #c0bec3;
    box-shadow: 3px 3px 5px #c0bec3;
    color: #fff;
    font: bold 14px Arial, Helvetica, sans-serif;
    text-align: center;
}

#divloading {top:0;right:0}
/*-- Print Map - Thank you page--*/
.print_map{margin-bottom:10px;text-align:left}
.print_map .rbh1{margin:0 3px}
.print_map .rbh2{margin:0 2px}
.print_map .rbh3{
    margin:0 1px;
    height:2px;
    border-left: 1px solid #cdcdcd;
    border-right: 1px solid #cdcdcd
}
.print_map .rbh2,.print_map .rbh3,.print_map .border_content{background-color:#f0f0f0}
.print_map .border_content{padding:2px 0;overflow:hidden}
.print_map a{
    cursor:pointer;
    height:26px;
    line-height:24px;
    display:inline-block;
    margin-left:10px
}
.print_map b.sprite{
    background-position:-201px -79px;
    float:left;
    height:26px;
    width:26px;
    margin-right:6px;
}

/*-- Print Map page--*/
/* Contain floats: h5bp.com/q */

.body_printmap{background-color:#fff}
.box_banner{
	background-color:#f5f5f5;
	border-bottom:1px solid #ccc;
	padding:10px;
}
.box_banner div,.hotel_detail{width:775px;margin:auto;color:#000}
    .box_banner a {
        background-color: #26ace0;
        border: solid 3px #86d7f7;
        color: #fff !important;
        cursor: pointer;
        font: bold x-large Arial, Helvetica, sans-serif;
        width: 145px;
        height: 32px;
        -moz-border-radius: 7px;
        -webkit-border-radius: 7px;
        border-radius: 7px;
        text-decoration: none;
        text-align: center;
        margin-top: 18px;
    }
.box_banner ul{float:left}
.box_banner li{list-style-position:inside;margin-bottom:3px}
.hotel_detail{margin:20px auto 0;padding-bottom:20px}
.hotel_detail textarea{color:#666;margin-top:8px;resize:none;overflow-y:scroll;width:770px}
.box_htlname{height:150px}
.box_htlname div{width:465px;float:left}
.fontlargeb{font:bold x-large Arial, Helvetica, sans-serif}
.fontmedium{font:normal medium Arial, Helvetica, sans-serif}
.box_htlname .fontlargeb{margin-top:10px}
.qrcode {
    background-color: #f5f5f5;
    -moz-border-radius: 10px;
    -webkit-border-radius: 10px;
    border-radius: 10px;
    color: #666;
    width: 310px;
    padding: 5px 0 10px;
}
.qrcode table{width:310px;margin:auto}
.qrcode table td,.qrcode table th{text-align:center;width:50%}
.qrcode table th{font-size:10px;padding:0 5px 5px}
.rightline{border-right:1px solid #ccc}
#map_canvas{border:2px solid #d4d4d4;margin:15px 0 20px;height:500px;width:770px}   
	
@media print 
{		
	textarea{
		border-style:none;
		height:250px;
		vertical-align:text-top;
	}  		
	.noPrint{ 
		display: none; 
	}
}


/* ----- promo note box ------*/
.promonotebox {
    color: #333;
    background: #fffedf;
    border: 2px solid #F79D11;
    -webkit-border-radius: 8px;
    -moz-border-radius: 8px;
    border-radius: 8px;
    padding: 12px 8px;
    margin-bottom: 20px;
    font-size: 12px;
    text-align: center;
}
/*----- BKG 2013 -----*/
.width-full { width:466px }
.width-halffull { width:340px }
.width-twothird { width:285px }
.width-onethird { width:151px }
.width-half { width:218px }
.width-title { width:86px }
.width-half-withTitle { width:160px }
.width-cvc { width:100px }
.bkg_divInputCol input[type='text'],
.bkg_divInputCol select,
#bkg_txtDiscountCode,
#txtPhoenix { width:100% }                            
.bkg_divInputCol.width-full input[type="text"] { width:461px }
.bkg_divInputCol.width-halffull input[type="text"] { width:335px }
.bkg_divInputCol.width-twothird input[type="text"] { width:280px }
.bkg_divInputCol.width-onethird input[type="text"] { width:146px }
.bkg_divInputCol.width-half input[type="text"],
.bkg_divInputCol .width-half input[type="text"] {
    width:213px;
}
.bkg_divInputCol.width-half-withTitle input[type="text"] { width:156px }
.bkg_divInputCol input[type='text'],
#divRewardsLoginOn .rewardsformwrapper input.inputtext,
.box_members input[type='text'] {
    padding-left: 4px;
    line-height: 22px\9;
}
/*----- Payments Info 2013-----*/
#bkg_divCardExpiry select {width: 103px}
#bkg_divCardNo input, #bkg_divCardNoAmex input {
    margin-right: 4px;
    width: 42.5px;
    _width: 39px;
}
#bkg_divCardNoAmex input {
     width: 52px;
    _width: 48px;
}
#bkg_divCardNoAmex input#txtAmex_1 {
    width: 79px;
    _width: 75px;
}
#bkg_divCardNo input#txtCard_3, #bkg_divCardNoAmex input#txtAmex_2 {margin-right: 0}
#divChkLatOffer { margin:2px 0 12px }
#divChkLatOffer label {
    margin-left: 18px;
    display: block;
}
#divChkLatOffer input {
    float: left;
    margin: 0px 5px 0 0;
    *margin-right: 2px;
}
#divChkNotMe input[type="checkbox"],
#guestHolder .hinttext input[type="checkbox"],
#guestHolder_2 .hinttext input[type="checkbox"]  {
    float: left;
    margin: 1px 5px 0 0;
}
#divChkNotMe { margin-top: 8px }
#txtAdditionalNotes {
    color: #959595;
    display: block;
    overflow: hidden;
    resize: none;
    width: 460px;
}                           
#guestHolder .hinttext,#guestHolder_2 .hinttext {
    margin:23px 0 0 0;
    width: auto;
}                            
#guestHolder .hinttext.withValidateOffset,
#guestHolder_2 .hinttext.withValidateOffset {
    margin-left: 24px;
}
#guestHolder,#guestHolder .hinttext input[type="checkbox"],#guestHolder_2 .hinttext input[type="checkbox"]{
    margin-right:3px;
    vertical-align:middle
}
.bggreybox {
    border: 1px solid #CDCDCD;
    margin-top:5px;
    background: #f9f9f9;
    padding:8px 0 10px 10px;
}
.bg_ef { background: #efefef }
/*----- Validators -----*/
input.error, select.error { border:1px solid #f00 !important}
input.valid, select.valid { border:1px solid #18AD5B !important}
label.error {color:#f00}
.valid-icon, .error-icon {
    width:24px;
    height:24px;
    position: absolute;
    top: 0px;
    *top:1px;
    right: -24px;
}
.error-icon { background:#f00 url(https://img.agoda.net/images/default/bookingform_sprite_v10.png) no-repeat; background-position:-490px -151px; }
.valid-icon { background:#18AD5B url(https://img.agoda.net/images/default/bookingform_sprite_v10.png) no-repeat; background-position:-460px -121px; }

.divError, .errorplacement {
    margin-top:-10px;
    padding-bottom: 10px;
    float: left;
}
#divPayment .bkg_divInputCol { *padding-bottom: 0 }
#errPaymentMethod.errorplacement { *float:none }
#divPayment .divError, .errorplacement { *margin-top:0 }
.divError label, .errorplacement label {
    display: block;
    line-height: 1.4em;
}
#errSum {
    color: #f00;
    font-weight: normal;
    padding: 0 8px 0 0;
}                            
#errSum li { list-style:none; margin-bottom: 2px; }
/* ---------- jQuery UI Tooltip ---------*/                            
.ui-widget { font: 14px Arial, Helvetica, sans-serif; }
.ui-widget-content {
    background: #cdcdcd;
    border: none;
    text-align: center;
}
.ui-tooltip { 
    max-width: 400px;
    padding:3px; 
    -webkit-box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.28);
    -moz-box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.28);
    box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.28);
}
.ui-tooltip .imagewrapper {
    -webkit-border-radius: 2px;
    -moz-border-radius: 2px;
    border-radius: 2px;
    padding: 2px;
    background: #fff;
}
.ui-tooltip img { max-width: 400px }
    .ui-tooltip .tooltipdesc {
        color: #000;
        padding: 4px 2px 2px;
        -webkit-text-shadow: 1px 1px 1px rgba(255,255,255,0.4);
        text-shadow: 1px 1px 1px rgba(255,255,255,0.4);
    }
/* Payment form */
#banner_bestPrice_ab { margin-right:0 }
#banner_bestPrice_ab a#bestprice { padding-left: 23px }
/* --------- error pages ------------*/
#popupwrapper .contentpopup{margin: 0;padding: 12px;height: 347px;overflow:auto;border:none; }
/* iPad [portrait + landscape] */
@media only screen and (min-device-width: 768px) and (max-device-width: 1024px){
    #wrapped{min-width:976px}
    #wrapper{padding:10px 0;max-width:976px}
    body{-webkit-text-size-adjust:none}
    input[type="checkbox"],#divChkLatOffer input[type="checkbox"],#divChkNotMe div input[type="checkbox"]{background-color:#fffedf;border:1px solid #8d9aa3}
}
/* iPhone [portrait + landscape] */
@media only screen and (max-device-width: 480px){
    #wrapped{min-width:976px}
    #wrapper{padding:10px 0;max-width:976px}
    body{-webkit-text-size-adjust:none}
    input[type="checkbox"],#divChkLatOffer input[type="checkbox"],#divChkNotMe input[type="checkbox"]{background-color:#fffedf;border:1px solid #8d9aa3}
}

/* Chrome only */
@media screen and (-webkit-min-device-pixel-ratio:0) {
    select { padding:0 }
}

/*----- fix ie6 -----*/
* html .width-full { width:458px }
* html .width-halffull { width:332px }
* html .width-twothird { width:277px }
* html .width-onethird { width:143px }
* html .width-half { width:210px }
* html .width-title { width:78px }
* html .width-half-withTitle { width:154px }
* html .width-cvc { width:94px }  
* html .width-cvc .relative { width:94px }  
* html .bkg_divInputCol input,
* html .bkg_divInputCol select,
* html #bkg_txtDiscountCode,
* html #txtPhoenix { width:100% }  
* html .width-full input { width:449px }
* html .width-halffull input { width:327px }
* html .width-twothird input { width:272px }
* html .width-onethird input { width:138px }
* html .width-half input { width:205px }
* html .width-half-withTitle input { width:148px }
* html .bkg_divInputCol input {
    height:22px;
    padding-left: 4px;
    line-height: 22px;
}
* html #divPayment .bkg_divInputCol { margin-right: 15px }
* html #bkg_divCardExpiry select { width:99px }
* html .box_members .inputtext {
    height: 22px;
    line-height: 22px;
    padding-left: 4px;
}
* html iframe.fixie6 {
    position: absolute;
    z-index: -1;
    filter: mask();
    border: 0;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background: none;
    width: 350px;
}
* html #divCountryIssuePopup .fixie6 { height: 60px }
* html #divWhichBankPopup .fixie6 { height: 155px }
* html #divCVCPopup .fixie6 { width: 600px; height: 355px }
* html .calloutDown {
    border-bottom-width: 0px;
    border-left-width: 0px;
    border-right-width: 0px;
    font-size: 0;
    line-height: 0;
    bottom: 5px;
}
* html .calloutDown2 {
    border-bottom-width: 0px;
}
* html .calloutUp {
    border-top-width: 0px;
    border-left-width: 0px;
    border-right-width: 0px;
    font-size: 0;
    line-height: 0;
    top:5px;
}
* html .calloutUp2 {
    border-top-width: 0px;
}
* html #divChkLatOffer {
    zoom:1;
}
* html #divAddress .valid-icon, * html #divAddress .error-icon{right:-20px}
/*----- end fix ie6 -----*/
