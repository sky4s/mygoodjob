var isBE3 = false; //check at returngetbookingdetails
var step = 1;
var isBookingCom = false;
var isFreeCan = false;

if (typeof hasRemainingRoom === 'undefined') {
    var hasRemainingRoom = false;
}

if (typeof nightText === 'undefined') {
    var nightText = '';
}

if (typeof pagetype === 'undefined') {
    var pagetype = 35;
}

//if (typeof is1656 === 'undefined') {
//    var is1656 = false;
//}

if (typeof isAppliedCB === 'undefined') {
    var isAppliedCB = false;
}

if (typeof ispartAppliedCB === 'undefined') {
    var ispartAppliedCB = false;
}

if (typeof is1678 === 'undefined') {
    var is1678 = false;
}

if (typeof is1693 === 'undefined') {
    var is1693 = false;
}

if (typeof is1751 === 'undefined') {
    var is1751 = false;
}

if (typeof is1788 === 'undefined') {
    var is1788 = false;
}
if (typeof ab1788 === 'undefined') {
    var ab1788 = {};
}

if (typeof showcollected === 'undefined') {
    var showcollected = false;
}

if (typeof isBookingCom === 'undefined') {
    var isBookingCom = false;
}

var modalClass = 'modalpopup';

function GetBookingDetail() {
    var urlMethod = getUrlMethod("book.aspx", "GetBookingDetail");
    var jsonData = "{}";
    SendAjax(urlMethod, jsonData, ReturnGetBookingDetail);

}

function ReturnGetBookingDetail(msg) {
    $("#bookingDetail").html("");
    $("#roomDetail").html("");
    $("#footerDetail").html("");
    $("#finalPrice").html("");
    $("#box_bkdcnote .price").html("");

    var ss = "";


    // Fill the hotel detail.
    var hotelname = msg.d.HotelDetails[0].HotelName;

    var rname = "";
    hotelname = msg.d.HotelDetails[0].HotelDisplayName;

    var roomNameTxt = function () {
        var rnameEN = msg.d.HotelDetails[0].RoomDetails[0].RoomName;
        var rnameFL = msg.d.HotelDetails[0].RoomDetails[0].TranslatedRoomName;
        var res = rnameEN;
        if ((rnameFL != "") && (rnameFL != null) && (rnameEN != rnameFL)) {
            res = rnameFL + cmsDomestic + " (" + rnameEN + ")";
        } else {
            res = res + cmsDomestic;
        }
        return res;
    } ();

    var strBookCondHtml = '';

    if (is1788) modalClass = 'modal-button';

    if (hasRemainingRoom) {

        $("#divUrgencyMsg").show();

        if (remainrooms >= 7 || remainrooms <= 0) {
            $("#divUrgencyMsg").css("background-color", "#009933");
        } else if (remainrooms <= 6 && remainrooms >= 2) {
            $("#divUrgencyMsg").css("background-color", "#F79D11");
        } else if (remainrooms == 1) {
            $("#divUrgencyMsg").css("background-color", "#FF0000");
        } else {
            $("#divUrgencyMsg").hide();
        }
    }

    var HotelMarkup = "";
    if (pagetype == 35) {
        var hotelimg = msg.d.HotelDetails[0].ImageSTDPath;

        if (is1788) {
            HotelMarkup = "<tr><td>" +
                "<div class='hoteldetails-title'><span class='blacklarge'>" + hotelname + "</span><i class='sprite starrating stars" + GetHotelStarRating + "'></i>";
            if (IsPPP)
                HotelMarkup += "<span class='iconwrapper'><i class='sprite ic-PPP absolute'></i></span>";
            HotelMarkup += "</div>";
            if (!(hotelimg == null || hotelimg == "")) {
                HotelMarkup += "<div class='hoteldetails-img-wrapper inline-block'><img id='hoteldetails-img' class='handcursor' src='" + hotelimg + "' width='96' height='74' title='" + hotelname + "'/></div>";
            }
            HotelMarkup += "<div class='hoteldetails-txt-wrapper inline-block'><table>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsLocation + "</strong></td><td class='hoteldetails-txt'>" + msg.d.HotelDetails[0].HotelLocation + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckin + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckInStr) + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckout + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckOutStr) + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cms.Stay + "</strong></td><td class='hoteldetails-txt'>" + msg.d.HotelDetails[0].NightsRoomsDetail + ", " + msg.d.HotelDetails[0].AdultsChildrenDetail + "</td></tr>";
            HotelMarkup += "</table></div>";
            HotelMarkup += "</td></tr>";

        } else {
            HotelMarkup = "<tr><td><table class='hoteldetails-table'><tr><td colspan='3' class='hoteldetails-title'><span class='blacklarge'>" + hotelname + "</span>";
            HotelMarkup += "<i class='sprite starrating stars" + GetHotelStarRating + "'></i>";
            if (IsPPP)
                HotelMarkup += "<span class='iconwrapper'><i class='sprite ic-PPP absolute'></i></span>";
            HotelMarkup += "</td></tr>";
            HotelMarkup += "<tr>";
            if (!(hotelimg == null || hotelimg == "")) {
                HotelMarkup += "<td rowspan='4' style='width:96px'>";
                HotelMarkup += "<img id='hoteldetails-img' class='handcursor' src='" + hotelimg + "' width='96' height='74' title='" + hotelname + "'/></td>";
            }
            HotelMarkup += "<td class='hoteldetails-txt-label'><strong>" + cmsLocation + "</strong></td><td class='hoteldetails-txt' style='width:294px'>" + msg.d.HotelDetails[0].HotelLocation + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckin + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckInStr) + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckout + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckOutStr) + "</td></tr>";
            HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cms.Stay + "</strong></td><td class='hoteldetails-txt'>" + msg.d.HotelDetails[0].NightsRoomsDetail + ", " + msg.d.HotelDetails[0].AdultsChildrenDetail + "</td></tr>";
            HotelMarkup += "</table></td></tr>";
        }

        $("#tblHotelDes").empty().append(HotelMarkup);

        var roomdesc = "";
        var roomImg = msg.d.HotelDetails[0].RoomDetails[0].RoomImagePath;
        if (roomImg == null || roomImg == '')
            roomImg = msg.d.HotelDetails[0].ImageSTDPath;

        roomdesc += "<tr>";
        if (!(roomImg == null || roomImg == '')) {
            roomdesc += "<td style='width:96px'><img id='roomdetails-img' class='handcursor' src='" + roomImg + "' width='96' height='74'/></td>";
        }
        roomdesc += "<td class='roomdetails-txt'><ul><li>" + roomNameTxt + "</li>";

        if (msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText != null && msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText != "") {
            roomdesc += "<li><span class='purpletext'>" + msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText + "</span></li>";
        }

        if (msg.d.HotelDetails[0].RoomDetails[0].Includes == cmsPriceIncludedBF || isFreeCan) {
            roomdesc += "<li>"
            if (msg.d.HotelDetails[0].RoomDetails[0].Includes == cmsPriceIncludedBF) {
                roomdesc += cmsBFIncluded; //  + ", " + "</td></tr></table>";
                if (isFreeCan)
                    roomdesc += ", ";
            }

            if (isFreeCan)
                roomdesc += cmsFreeCancellation;
            roomdesc += "</li>";
        }

        roomdesc += "<li>" + msg.d.HotelDetails[0].NightsRoomsDetail + ", " + msg.d.HotelDetails[0].AdultsChildrenDetail;

        if (($("#bkg_pnlExtrabedOccFree").find(":checked").length > 0) || (msg.d.HotelDetails[0].RoomDetails[0].ExtraBedCharge != null)) {
            roomdesc += " - " + cms.ebincluded;
        } else {
            roomdesc += " - " + cms.ebexcluded;
        }

        roomdesc += "</li>";
        roomdesc += "</ul></td></tr>";
        $("#tblRoomDes").html("");
        $("#tblRoomDes").append(roomdesc);
        $("#pnlHotel").hide();
    } else {
        var hotelimg = msg.d.HotelDetails[0].ImageSTDPath;

        HotelMarkup = "<tr><td><table id='tblTYHotelDetails' class='hoteldetails-table'>";
        HotelMarkup += "<tr><td class='hoteldetails-hotelname' colspan='3'><span class='blacklarge'>" + hotelname + "</span>";
        HotelMarkup += "<i class='sprite starrating stars" + rating + "'></i>";
        if (IsPPP)
            HotelMarkup += "<span class='iconwrapper'><i class='sprite ic-PPP absolute'></i></span>";

        HotelMarkup += "</td></tr>";
        HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsLocation + "</strong></td><td class='hoteldetails-txt' style='width:294px'>" + msg.d.HotelDetails[0].HotelLocation + "</td>";
        HotelMarkup += "<td rowspan='4'><div class='hoteldetails-image-wrapper'><img src='" + msg.d.HotelDetails[0].ImagePath + "' width='96' height='74'></div><p class='clear'></p></td></tr>";
        HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckin + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckInStr) + "</td></tr>";
        HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cmsCheckout + "</strong></td><td class='hoteldetails-txt'>" + stringtoDate1669(msg.d.HotelDetails[0].CheckOutStr) + "</td></tr>";
        HotelMarkup += "<tr><td class='hoteldetails-txt-label'><strong>" + cms.Stay + "</strong></td><td class='hoteldetails-txt'>" + msg.d.HotelDetails[0].NightsRoomsDetail + ", " + msg.d.HotelDetails[0].AdultsChildrenDetail + "</td></tr>";

        if (isAppliedCB || ispartAppliedCB) {
            HotelMarkup += "<tr class='bksum-roomname'><td colspan='3' class='bksum-roomname-TY-toppadding'><table class='bkgdt_width'><tr><td class='bkgdt_col1'><span class='blackbold'>" + roomNameTxt + "</span> <span class='pernight'>" + cms.PerNight + GetRateDescriptionHover() + "</span></td>";
            HotelMarkup += "<td class='bkgdt_col2 blackbold'>" + msg.d.HotelDetails[0].RoomDetails[0].RoomCharge.LocalCurrency + "</td>";

            if (is1693) {
                HotelMarkup += "<td class='bkgdt_col3 blackbold'>" + msg.d.HotelDetails[0].RoomDetails[0].ExTaxAmountIncluded + "</td></tr></table></td></tr>";
            } else {
                HotelMarkup += "<td class='bkgdt_col3 blackbold'>" + msg.d.HotelDetails[0].RoomDetails[0].RoomCharge.LocalAmount + "</td></tr></table></td></tr>";
            }

            HotelMarkup += "<tr><td colspan='3' class='xsmallgrey'>" + cms.NightForText + "</td></tr>";

        } else {
            HotelMarkup += "<tr><td class='hoteldetails-title' colspan='3'>" + msg.d.HotelDetails[0].NoOfRooms + ' x ' + roomNameTxt + "</td></tr>";
        }

        if (msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText != null && msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText != "") {
            HotelMarkup += "<tr><td class='hoteldetails-title' colspan='3'><span class='purpletext'>" + msg.d.HotelDetails[0].RoomDetails[0].YCSPromotionText + "</span></td></tr>";
        }

        if (msg.d.HotelDetails[0].RoomDetails[0].Includes == cmsPriceIncludedBF) {
            HotelMarkup += "<tr style='line-height: 20px;'><td colspan='3'><span>" + cmsBFIncluded + "</span></td></tr>";
        }

        // Extrabed.
        if (is1693 && msg.d.HotelDetails[0].RoomDetails[0].ExtraBedCharge != null && msg.d.TotalExtrabedDecimal > 0) {
            var extrabedCharge = msg.d.TotalExtrabed;

            HotelMarkup += "<tr><td colspan='3'>" +
                            "<table class='bkgdt_width'>" +
                                "<tr class='bksum-extrabed text-12px' style='line-height: 20px;'>" +
                                    "<td class='bkgdt_col1'><span>" + cmsExtraBedCharge + "</span></td>" +
                                    "<td class='bkgdt_col2'><span>" + msg.d.HotelDetails[0].RoomDetails[0].ExtraBedCharge.LocalCurrency + "</span></td>" +
                                    "<td class='bkgdt_col3'><div class='relative'><span>" + extrabedCharge + "</span></div></td>" +
                                "</tr>" +
                            "</table>" +
                            "</td></tr>";
            //            HotelMarkup += "<tr class='bksum-extrabed text-12px' style='line-height: 20px;'><td class='bkgdt_col1'>" + cmsExtraBedCharge + "</td><td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[0].ExtraBedCharge.LocalCurrency + "</td><td class='bkgdt_col3'>" + extrabedCharge + "</td></tr>";

        }

        // Cancellation Policy.
        if (!isBE3) {
            if (msg.d.HotelDetails[0].RoomDetails[0].CancellationPolicy != null && msg.d.HotelDetails[0].RoomDetails[0].CancellationPolicy != "") {
                if (isFreeCan == true) {
                    var strlink = "";
                    strlink = "<div class='inline-block'><span class='bkg_freecan' style='line-height: 20px;'>" + $.trim(cms["cmsFreeCancellation"]) + "</span>";
                    strBookCondHtml = "<div class='pnlmouseoverBookCond'>" + strlink + "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_BookCond" + i + "'><span class='inline-block sprite ic-question'></span><div style='display: none;' class='popup_body' id='divBookCondPopup" + i + "'><div class='popup_header_promotion'><p><span class='inline-block sprite ic-title-popup'></span>" + cms["FreeCanH"] + "</p></div><div style='' class='popup_content_promotion'><span style='text-decoration: none;'>" + cms["FreeCan"] + "</span></div></div><div class='calloutDown' id='divBookCondCallout" + i + "' style='display:none;'><div class='calloutDown2' style='display:none;'></div></div></div></div></div></div></td><p class='clear'></p></tr>";
                    HotelMarkup += "<tr><td colspan='3'>" +
                        strBookCondHtml +
                        "<p class='clear'></p></td></tr>";
                }
                else {
                    strBookCondHtml = "<div class='pnlmouseoverBookCond'>" +
                        "<div class='inline-block'>";
                    if (is1788) {
                        strBookCondHtml += "<a href='" + "/b/popups/ContentPopup.aspx?width=785&height=455&noborder=1&content=44907&p=" + p + "' LoadingPosition='in' class='" + modalClass + " bookingcond' style='line-height: 20px;' oncontextmenu='return false;' popupTitle='" + cmsBookingConditions + "'>" + $.trim(cmsBookingConditions) + "</a>";
                    } else {
                        strBookCondHtml += "<a href='" + "/b/popups/BookingConditions.aspx?height=auto&width=702&modal=true&p=" + p + "' class='thickbox bookingcond' style='line-height: 20px;'>" + $.trim(cmsBookingConditions) + "</a>";
                    }
                    strBookCondHtml += "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_BookCond" + i + "'>" + "<span class='inline-block sprite ic-question'></span><div style='display: none;' class='popup_body' id='divBookCondPopup" + i + "'><div class='popup_header_promotion'><p><span class='inline-block sprite ic-title-popup'></span>" + cms["BookCondH"] + "</p>" + "</div><div style='' class='popup_content_promotion'><span style='text-decoration: none;'>" + cms["BookCond"] + "</span></div></div><div class='calloutDown' id='divBookCondCallout" + i + "' style='display:none;'><div class='calloutDown2' style='display:none;'></div></div></div></div></div></div>";
                    HotelMarkup += "<tr><td colspan='3'>" + strBookCondHtml + "<p class='clear'></p></td></tr>";
                }
            }
        }

        if (is1693 && cms.GetFooterText.length) {
            HotelMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey'>" + cms.GetFooterText + "</div></td></tr>";

            if (msg.d.FinalPriceIncludedExcludedTax != null && msg.d.FinalPriceIncludedExcludedTax != "" && msg.d.FinalPriceIncludedExcludedTax != "0") {
                HotelMarkup += "<tr><td colspan='3'>" +
                    "<table class='bkgdt_width blackbold'>" +
                        "<tr id='trTYFinalPrice'>" +
                            "<td class='bkgdt_col1'><span>" + cmsFinalPrice + " " + cms.NightText + "</span></td>" +
                            "<td class='bkgdt_col2'><span>" + msg.d.CurrencyCode + "</span></td>" +
                            "<td class='bkgdt_col3'><div class='relative'><span>" + msg.d.FinalPriceIncludedExcludedTax + "</span><div class='bksum-finalprice-border'></div></div></td>" +
                        "</tr>" +
                    "</table>" +
                    "</td></tr>";
            }
        }


        HotelMarkup += "</table></td></tr>";

        $("#bookingDetail").append(HotelMarkup);
        $("#pnlHotel").show();
    }

    if (!(is1788 && (ab1788.isPhoneView() || isTouchDevice() || isiPad() || isiPhone()))) {
        //jQuery UI Tooltip
        $(document).tooltip({
            items: '#hoteldetails-img, #roomdetails-img',
            content: function () {
                var elem = $(this);
                if (elem.is('#hoteldetails-img') && hotelimg != null && hotelimg != '') {
                    return '<div class="imagewrapper"><img src="' + hotelimg + '" ></div><div class="tooltipdesc">' + hotelname + '</div>';
                }
                else if (elem.is('#roomdetails-img') && roomImg != null && roomImg != '') {
                    return '<div class="imagewrapper"><img src="' + roomImg + '" ></div><div class="tooltipdesc">' + roomNameTxt + '</div>';
                }
            },
            position: {
                my: "left+5 middle",
                at: "right middle",
                collision: "flipfit"
            }
        });
    }

    if ($("#roomDetail").length) {
        // Fill the Room detail.
        var RoomMarkup = "";
        var maxAmountlen = 0;

        var nights = 1;
        if (msg.d.HotelDetails[0].NoOfNights > 1)
            nights = msg.d.HotelDetails[0].NoOfNights;

        // Cancellation Policy.
        if (!isBE3) {
            if (msg.d.HotelDetails[0].RoomDetails[0].CancellationPolicy != null && msg.d.HotelDetails[0].RoomDetails[0].CancellationPolicy != "") {
                var strlink = "";
                var strlink1755 = "";

                if (isFreeCan) {
                    strlink = "<div class='inline-block'><a href='" + "/b/popups/ContentPopup.aspx?width=785&height=455&noborder=1&content=44907&p=" + p + "' LoadingPosition='in' class='"+ modalClass +" bookingcond' style='line-height: 20px;' oncontextmenu='return false;' popupTitle='" + cmsBookingConditions + "'>" + $.trim(cmsFreeCancellation) + "</a>";
                    strlink1755 = "<div class='inline-block'><a id='link1755' href='" + "/b/popups/ContentPopup.aspx?width=785&height=455&noborder=1&content=44907&p=" + p + "' LoadingPosition='in' class='" + modalClass + " bookingcond' style='line-height: 20px;' oncontextmenu='return false;' popupTitle='" + cmsBookingConditions + "'>" + $.trim(cmsBookingConditions1755) + "</a>";
                    strBookCondHtml = "<div class='pnlmouseoverBookCond'>" + strlink + "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_BookCond0'><span class='inline-block sprite ic-question'></span><div style='display: none;' class='popup_body' id='divBookCondPopup0'><div class='popup_header_promotion' ><p><span class='inline-block sprite ic-title-popup'></span>" + FreeCanH + "</p></div><div style='' class='popup_content_promotion'><span style='text-decoration: none;'>" + FreeCan + "</span></div></div><div class='calloutUp' id='divBookCondCallout0' style='display:none;'><div class='calloutUp2' style='display:none;'></div></div></div></div></div></div>";
                }
                else {
                    strlink = "<div class='inline-block'><a href='" + "/b/popups/ContentPopup.aspx?width=785&height=455&noborder=1&content=44907&p=" + p + "' LoadingPosition='in' class='" + modalClass + " bookingcond' style='line-height: 20px;' oncontextmenu='return false;' popupTitle='" + cmsBookingConditions + "'>" + $.trim(cmsBookingConditions) + "</a>";
                    strlink1755 = "<div class='inline-block'><a id='link1755' href='" + "/b/popups/ContentPopup.aspx?width=785&height=455&noborder=1&content=44907&p=" + p + "' LoadingPosition='in' class='" + modalClass + " bookingcond' style='line-height: 20px;' oncontextmenu='return false;' popupTitle='" + cmsBookingConditions + "'>" + $.trim(cmsBookingConditions1755) + "</a>";
                    strBookCondHtml = "<div class='pnlmouseoverBookCond'>" + strlink + "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_BookCond0'>" + "<span class='inline-block sprite ic-question'></span><div style='display: none;' class='popup_body' id='divBookCondPopup0'><div class='popup_header_promotion' ><p><span class='inline-block sprite ic-title-popup'></span>" + BookCondH + "</p>" + "</div><div style='' class='popup_content_promotion'><span style='text-decoration: none;'>" + BookCond + "</span></div></div><div class='calloutUp' id='divBookCondCallout0' style='display:none;'><div class='calloutUp2' style='display:none;'></div></div></div></div></div></div>";
                }
            }
        }

        if (pagetype == 35) {
            RoomMarkup += "<tr><td colspan='3' class='roomtitle'>" +
                "<span class='blacklarge'>" + cmsBookSum + "</span>" +
                strBookCondHtml +
                "</td></tr>";

            //BKG280/1755
            if ($("#divAB1755").length > 0) {
                var addlinkName = "";
                if ($("#divAB1755").find($("#linkTC1755")).length > 0) {
                    addlinkName = $("#divAB1755").html();
                } else {
                    addlinkName = $("#divAB1755").html().replace("<a", "<a id='linkTC1755'");
                }
                var context1755 = addlinkName.replace("{1}", strlink1755);
                $("#divAB1755").empty().html(context1755);
            }
        }

        for (var i = 0; i < msg.d.HotelDetails[0].RoomDetails.length; i++) {

            var rnameEN = msg.d.HotelDetails[0].RoomDetails[i].RoomName;
            var rnameFL = msg.d.HotelDetails[0].RoomDetails[i].TranslatedRoomName;

            if (pagetype == 35) {
                RoomMarkup += "<tr class='bksum-roomname'>";

                var roomNameTxt = rnameEN;
                if ((rnameFL != "") && (rnameFL != null) && (rnameEN != rnameFL)) {
                    roomNameTxt = rnameFL + cmsDomestic + " (" + rnameEN + ")";
                }
                else {
                    roomNameTxt = roomNameTxt + cmsDomestic;
                }

                if (isAppliedCB || ispartAppliedCB) {
                    RoomMarkup += "<td class='bkgdt_col1' style='padding-top:10px;'><span class='blackbold'>" + roomNameTxt + "</span> <span class='pernight'>" + cms.PerNight + GetRateDescriptionHover() + "</span></td>";
                    RoomMarkup += "<td class='bkgdt_col2 blackbold' style='padding-top:10px;'>" + msg.d.HotelDetails[0].RoomDetails[i].RoomCharge.LocalCurrency + "</td>";
                    if (is1693) {
                        RoomMarkup += "<td class='bkgdt_col3 blackbold' style='padding-top:10px;'>" + msg.d.HotelDetails[0].RoomDetails[i].ExTaxAmountIncluded + "</td></tr>";
                    } else {
                        RoomMarkup += "<td class='bkgdt_col3 blackbold' style='padding-top:10px;'>" + msg.d.HotelDetails[0].RoomDetails[i].RoomCharge.LocalAmount + "</td></tr>";
                    }

                    RoomMarkup += "<tr><td colspan='3' class='xsmallgrey'>" + cms.NightForText + "</td></tr>";
                } else {
                    RoomMarkup += "<td colspan='3'>" + msg.d.HotelDetails[0].NoOfRooms + ' x ' + roomNameTxt + "</td></tr>";
                }              
            }

            var localAmount = msg.d.HotelDetails[0].RoomDetails[i].RoomCharge.LocalAmount;
            var totalRoomAmount = roomratetotal;

            if (msg.d.IsMSE) {
                if (msg.d.MSEItem != null) {
                    localAmount = msg.d.MSEItem.RoomChargePerNight;
                    totalRoomAmount = msg.d.MSEItem.TotalRoomcharge;
                }
            }

            if (msg.d.HotelDetails[0].RoomDetails[i].YCSPromotionText != null && msg.d.HotelDetails[0].RoomDetails[i].YCSPromotionText != "") {

                if (pagetype == 35) {
                    ss = "<tr style='line-height: 20px;'><td colspan='3'><p class='roompro' style='line-height: 20px;'>" + msg.d.HotelDetails[0].RoomDetails[i].YCSPromotionText + "</p></td></tr>";   
                } else {
                    ss = "<tr style='line-height: 20px;'><td colspan='3'><p style='font-size: x-small;line-height: 20px;'>" + msg.d.HotelDetails[0].RoomDetails[i].YCSPromotionText + "</p></td></tr>";
                }
                RoomMarkup += ss;
            }

            //var flag = is1656 && cms["RoomIncluded"] != '';
            //// Breakfast
            if (msg.d.HotelDetails[0].RoomDetails[i].Includes != null && msg.d.HotelDetails[0].RoomDetails[i].Includes != "") {

                if (msg.d.HotelDetails[0].RoomDetails[i].Includes == cmsPriceIncludedBF) {
                    RoomMarkup += "<tr class='bksum-breakfast' style='line-height: 20px;'><td colspan='3'><span>" + cmsBFIncluded + "</span></td></tr>";
                } else {
                    if (!(isAppliedCB || ispartAppliedCB)) {
                        RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><span>" + msg.d.HotelDetails[0].RoomDetails[i].Includes + "</span></td></tr>";
                    }
                }
            }

            if (!(isAppliedCB || ispartAppliedCB)) {
                RoomMarkup += "<tr class='bksum-amount' style='line-height: 20px;'><td class='bkgdt_col1'>";
                RoomMarkup += msg.d.HotelDetails[0].RoomDetails[i].RoomCharge.LocalCurrency + " " + localAmount + " " + nightText + "</span></td><td class=' bkgdt_col2'><span>" + msg.d.HotelDetails[0].RoomDetails[i].RoomCharge.LocalCurrency + "</span></td><td class='bkgdt_col3'><span>" + totalRoomAmount + "</span></td></tr>";
            }

            if (msg.d.HasDiscount) {
                RoomMarkup += "<tr class='bksum-discount text-12px' style='line-height: 20px;'><td class='bkgdt_col1'>";
                RoomMarkup += "<span class='dir-ltr'>" + msg.d.DiscountText + "</span></td><td class=' bkgdt_col2' ><span>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span>-" + $.trim(msg.d.Discount) + "</span></td></tr>";
            }

            if (msg.d.HasReward) {
                RoomMarkup += "<tr class='bksum-rewards text-12px' style='line-height: 20px;'><td class='bkgdt_col1'>";
                RoomMarkup += "<span>Rewards Saving</span></td><td class='bkgdt_col2' ><span>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span>-" + $.trim(msg.d.RewardSaving) + "</span></td></tr>";
            }

            if (!(isAppliedCB || ispartAppliedCB)) {
                //// Excludes.
                if (msg.d.HotelDetails[0].RoomDetails[i].Excludes != null && msg.d.HotelDetails[0].RoomDetails[i].Excludes != "") {
                    //                    if (is1656) {
                    //                        if (cms["RoomExcluded"] != '')
                    //                            RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><span>" + cms["RoomExcluded"] + "</span></td></tr>";
                    //                    } else {
                    RoomMarkup += "<tr class='bksum-excludes' style='line-height: 20px;'><td colspan='3'><span>" + msg.d.HotelDetails[0].RoomDetails[i].Excludes + "</span></td></tr>";
                    //}
                }
            }

            // Extrabed.
            if (msg.d.HotelDetails[0].RoomDetails[i].ExtraBedCharge != null && msg.d.TotalExtrabedDecimal > 0) {
                var extrabedCharge = msg.d.TotalExtrabed;
                if (pagetype == 35) {
                    RoomMarkup += "<tr class='bksum-extrabed text-12px' style='line-height: 20px;'><td class='bkgdt_col1'>" + cmsExtraBedCharge + "</td><td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[i].ExtraBedCharge.LocalCurrency + "</td><td class='bkgdt_col3'>" + extrabedCharge + "</td></tr>";
                } else {
                    RoomMarkup += "<tr class='xsmallgrey' style='line-height: 20px;'><td class='bkgdt_col1'>" + cmsExtraBedCharge + "</td><td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[i].ExtraBedCharge.LocalCurrency + "</td><td class='bkgdt_col3'>" + extrabedCharge + "</td></tr>";
                }
            }

            if (!isAppliedCB) {
                var surchargedIncluded = msg.d.MSEItem != null && msg.d.MSEItem.MSEConfig != null && msg.d.MSEItem.MSEConfig.IncludeSurcharge && !ispartAppliedCB;
                // Surcharges.
                if (msg.d.HotelDetails[0].RoomDetails[0].Surcharge.length > 0) {
                    if (surchargedIncluded) {
                        RoomMarkup += "<tr><td colspan='3' style='padding-top:10px;'>" + cmsCompulsoryIncluded + "</td></tr>";
                    } else {
                        if (ispartAppliedCB) {
                            RoomMarkup += "<tr><td colspan='3' class='xsmallgrey' style='padding-top:10px;'>" + cmsCompulsory + "</td></tr>";
                        } else {
                            RoomMarkup += "<tr><td colspan='3' style='padding-top:10px;'>" + cmsCompulsory + "</td></tr>";
                        }
                    }
                }

                for (var j = 0; j < msg.d.HotelDetails[0].RoomDetails[0].Surcharge.length; j++) {
                    if (msg.d.IsMSE && !ispartAppliedCB) {
                        if (surchargedIncluded) {
                            RoomMarkup += "<tr class='bksum-surcharges' style='line-height: 20px;'><td colspan='3'>+ " + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].ChargeName + "</td>";
                        } else {
                            RoomMarkup += "<tr class='bksum-surcharges' style='line-height: 20px;'><td class='bkgdt_col1'>+ " + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].ChargeName + "</td>";
                            RoomMarkup += "<td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalCurrency;
                            RoomMarkup += "</td><td class='bkgdt_col3'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalAmount + "</td>";
                        }
                        RoomMarkup += "</tr>";
                    } else {
                        if (ispartAppliedCB) {
                            RoomMarkup += "<tr class='bksum-surcharges xsmallgrey' style='line-height: 20px;'><td class='bkgdt_col1'>+ " + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].ChargeName + "</td>";
                            RoomMarkup += "<td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalCurrency;
                            RoomMarkup += "</td><td class='bkgdt_col3'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalAmount + "</td>";
                            RoomMarkup += "</tr>";
                        } else {
                            RoomMarkup += "<tr class='bksum-surcharges' style='line-height: 20px;'><td class='bkgdt_col1'>+ " + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].ChargeName + "</td>";
                            RoomMarkup += "<td class=' bkgdt_col2'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalCurrency;
                            RoomMarkup += "</td><td class='bkgdt_col3'>" + msg.d.HotelDetails[0].RoomDetails[0].Surcharge[j].LocalAmount + "</td>";
                            RoomMarkup += "</tr>";
                        }
                    }
                }
            }

            //var tax = msg.d.HotelDetails[0].RoomTaxNumeric * nights; //totaltax;

            var taxstr = msg.d.TotalTax; //"0";               
            var cmsTaxLn = cmsHotelTax;
            var prceefee = 0;

            if (msg.d.IsMSE) {
                if (msg.d.MSEItem != null && msg.d.MSEItem.MSEConfig != null) {
                    if (!msg.d.MSEItem.MSEConfig.IncludeSaleTax) {
                        cmsTaxLn = cms["SaleTax"];
                        taxstr = msg.d.MSEItem.TotalSaleTax;
                    }

                    if (!msg.d.MSEItem.MSEConfig.IncludeServiceCharge) {
                        prceefee = msg.d.MSEItem.ServiceChargePerNight;
                    }
                }
            }

            if (msg.d.HotelDetails[0].RoomTaxNumeric != 0) {
                if (!isBE3) {
                    if (isAppliedCB) {
                        if (cms.TaxDetailStep1.length)
                            RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.TaxDetailStep1 + "</div></td></tr>";
                        //                        if (is1693 && cms.GetFooterText.length)
                        //                            RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.GetFooterText + "</div></td></tr>";
                        //                        else //if (cms.TaxDetailStep1.length)                            
                        //                                RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.TaxDetailStep1 + "</div></td></tr>";                        
                    } else if (ispartAppliedCB) {
                        if (is1678 && cms.ExcludedForPartialStep11678.length) {
                            RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;padding-top:5px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.ExcludedForPartialStep11678 + "</div></td></tr>";
                        } else {
                            RoomMarkup += "<tr class='bksum-taxfee' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey'>" + cmsTaxLn + " " + nightText + " ";
                            RoomMarkup += msg.d.CurrencyCode + " " + taxstr + "</div></td></tr>";
                        }
                    } else {
                        if ((!msg.d.IsMSE) || (msg.d.IsMSE && msg.d.MSEItem != null && msg.d.MSEItem.MSEConfig != null && !msg.d.MSEItem.MSEConfig.IncludeSaleTax)) {
                            RoomMarkup += "<tr class='bksum-taxfee' style='line-height: 20px;'><td class='bkgdt_col1'><div class='pnlmouseoverTaxFee'>";

                            RoomMarkup += "+ <a href='javascript:void(0)' class='bookingcond' id='lnkHover_TaxFee' style='line-height: 20px;'>";
                            RoomMarkup += "<span class='ui-blue-link'>" + cmsTaxLn + "</span>";
                            RoomMarkup += "</a><span class='inline-block' style='padding-left: 5px;'>" + nightText + "</span>";

                            RoomMarkup += "<div class='ico_qstion_wrapper'>";

                            RoomMarkup += "<div class='ico_qstion absolute' ><div class='iconquestion' id='imgIcon_TaxFee'>";
                            RoomMarkup += "<span class='inline-block sprite ic-question'></span>";
                            RoomMarkup += "<div class='popup_body hide' id='divTaxFeePopup'><div class='popup_header_promotion' ><p><span class='inline-block sprite ic-title-popup'></span>" + TaxFeeH + "</p>"
                            + "</div><div class='popup_content_promotion' >" + TaxFee + "</div></div>" + "<div class='calloutDown hide' id='divTaxFeeCallout'><div  class='calloutDown2' ></div></div></div></div>";

                            RoomMarkup += "</div>";

                            RoomMarkup += "</div></td>";
                            RoomMarkup += "<td class='bkgdt_col2' ><span>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span>" + taxstr + "</span></td></tr>";
                        }

                        if (prceefee > 0) {
                            RoomMarkup += "<tr class='bksum-taxfee' style='line-height: 20px;'><td class='bkgdt_col1'><div class='pnlmouseoverTaxFee'>";

                            RoomMarkup += "+ <a href='javascript:void(0)' class='bookingcond' id='lnkHover_TaxServiceFee' style='line-height: 20px;'>";
                            RoomMarkup += "<span class='ui-blue-link'>" + cms["ServiceFee"] + "</span>";
                            RoomMarkup += "</a><span class='inline-block' style='padding-left: 5px;'>" + nightText + "</span>";

                            RoomMarkup += "<div class='ico_qstion_wrapper'>";

                            RoomMarkup += "<div class='ico_qstion absolute' ><div class='iconquestion' id='imgIcon_TaxServiceFee'>";
                            RoomMarkup += "<span class='inline-block sprite ic-question'></span>";
                            RoomMarkup += "<div class='popup_body hide' id='divTaxServiceFeePopup'><div class='popup_header_promotion' ><p><span class='inline-block sprite ic-title-popup'></span>" + cms["TaxServiceFee"] + "</p>"
                            + "</div><div class='popup_content_promotion' >" + TaxFee + "</div></div>" + "<div class='calloutDown hide' id='divTaxServiceFeeCallout'><div  class='calloutDown2' ></div></div></div></div>";

                            RoomMarkup += "</div>";

                            RoomMarkup += "</div></td><td class='bkgdt_col2' ><span>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span>" + msg.d.MSEItem.TotalServiceCharge + "</span></td></tr>";
                        }
                    }
                } else {
                    RoomMarkup += "<tr class='bksum-taxfee' style='line-height: 20px;'><td class='bkgdt_col1'>" + cmsBE3HotelTax;
                    RoomMarkup += "<span class='inline-block' style='padding-left: 5px;'>" + nightText + "</span>";
                    RoomMarkup += "</td><td class='bkgdt_col2' ><span>" + msg.d.CurrencyCode +
                        "</span></td><td class='bkgdt_col3'><span>" + taxstr + "</span></td></tr>";
                }
            } else {
                if (is1693 && cms.GetFooterText.length) {
                    RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey'>" + cms.GetFooterText + "</div></td></tr>";

                    if (msg.d.FinalPriceIncludedExcludedTax != null && msg.d.FinalPriceIncludedExcludedTax != "" && msg.d.FinalPriceIncludedExcludedTax != "0") {
                        RoomMarkup += "<tr id='trFinalPrice'>" +
                            "<td class='bkgdt_col1'><span class='blackbold'>" + cmsFinalPrice + " " + cms.NightText + "</span></td>" +
                            "<td class='bkgdt_col2'><span class='blackbold'>" + msg.d.CurrencyCode + "</span></td>" +
                            "<td class='bkgdt_col3'><div class='relative'><span class='blackbold'>" + msg.d.FinalPriceIncludedExcludedTax + "</span><div class='bksum-finalprice-border'></div></div></td>" +
                            "</tr>";
                    }

                } else if (isAppliedCB && cms.TaxDetailStep1.length && step == 1) {
                    RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.TaxDetailStep1 + "</div></td></tr>";
                } else {
                    if (is1678 && cms.ExcludedForPartialStep11678.length && step == 1) {
                        RoomMarkup += "<tr class='bksum-includes' style='line-height: 20px;'><td colspan='3'><div id='notincluded' class='xsmallgrey' style='padding-top:3px;'>" + cms.ExcludedForPartialStep11678 + "</div></td></tr>";
                    }
                }
            }
        }

        $("#roomDetail").append(RoomMarkup);
    }


    if (msg.d.HotelDetails[0].RoomTaxNumeric <= 0 && msg.d.HotelDetails[0].RoomDetails[0].ExTaxAmountIncludedDecimal > 0) {
        $("#ExcludedTaxDetail").empty();

        var collectHotel = "";
        var ispass = false;

        collectHotel += "<tr><td colspan='3'>" + cms.CollectHotel + ":</td></tr>";
        for (var i = 0; i < msg.d.HotelDetails[0].RoomDetails[0].TaxBreakdown.length; i++) {
            var taxobj = msg.d.HotelDetails[0].RoomDetails[0].TaxBreakdown[i];
            if (taxobj.Option != 5)
                continue;

            //            if (taxobj.Description.toLowerCase() == "resort fee" && !is1678) {
            //                continue;
            //            }

            var desc = taxobj.Description;
            if (desc.toLowerCase() == 'sum') {
                desc = cms.HotelTaxAndFee;
            }

            collectHotel += "<tr><td class='bkgdt_col1'>" + desc;

            if (taxobj.Type == 1) {
                collectHotel += " " + taxobj.Value + "%";
            }

            // if (this.Book.BookingItem.Hotels[0].Rooms[0].DmcID == 3038 || tx.Description.Trim().ToLower() == "city tax" || tx.Description.Trim().ToLower() == "resort fee")
            //            if (taxobj.Type != 1 && (isBookingCom || taxobj.Description.toLowerCase() == "city tax" || taxobj.Description.toLowerCase() == "resort fee")) {
            //                collectHotel += "</td><td class='bkgdt_col2' >" + msg.d.CurrencyCode + "</td><td class='bkgdt_col3'>" + taxobj.Value + "</td></tr>";
            //            } else {
            if (isBookingCom)
                collectHotel += "</td><td class='bkgdt_col2' >" + taxobj.CurrencyReq + "</td><td class='bkgdt_col3'>" + taxobj.CurrencyReqAmountString + "</td></tr>";
            else
                collectHotel += "</td><td class='bkgdt_col2' >" + taxobj.Currency + "</td><td class='bkgdt_col3'>" + taxobj.CurrencyAmountString + "</td></tr>";

            ispass = true;
        }

        $("#ExcludedTaxDetail").append(collectHotel);

    }

    //if ($("#footerDetail").length) {
    // Fill the footer.
    var FooterMarkup = "";

    // Fill the footer.
    var FinalMarkup = "";
    //Shows FinalPrice with bookingdotcom and BE3 conditions
    if (msg.d.FinalPrice != null && msg.d.FinalPrice != "" && msg.d.FinalPrice != "0") {
        if (is1693) {
            FinalMarkup += "<tr><td class='bkgdt_col1'><span class='blackbold'>" + cms.PayToday + "</span></td><td class='bkgdt_col2' ><span class='blackbold'>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span class='blackbold'>" + msg.d.FinalPrice + "</span></td></tr>";
        } else if (isAppliedCB) {
            FinalMarkup += "<tr><td class='bkgdt_col1'><span class='blackbold'>" + cmsFinalPrice + " " + cms.NightText + "</span></td><td class='bkgdt_col2' ><span class='blackbold'>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span class='blackbold'>" + msg.d.FinalPrice + "</span></td></tr>";
            if (cms.TaxDetailStep2.length)
                FinalMarkup += "<tr class='trFinalPriceHint'><td colspan='3'><span class='xsmallgrey'>" + cms.TaxDetailStep2 + "</span></td></tr>";
        } else if (ispartAppliedCB) {
            FinalMarkup += "<tr><td class='bkgdt_col1'><span class='blackbold'>" + cmsFinalPrice + " " + cms.NightText + "</span></td><td class='bkgdt_col2' ><span class='blackbold'>" + msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span class='blackbold'>" + msg.d.FinalPrice + "</span></td></tr>";

            if (is1678 && cms.ExcludedForPartialStep21678.length) {
                FinalMarkup += "<tr class='trFinalPriceHint'><td colspan='3'><span class='xsmallgrey'>" + cms.ExcludedForPartialStep21678 + "</span></td></tr>";
            } else {
                if (cmsPriceIncludesAll.length)
                    FinalMarkup += "<tr class='trFinalPriceHint'><td colspan='3'><span class='xsmallgrey'>" + cmsPriceIncludesAll + "</span></td></tr>";
            }

        } else {
            if (pagetype == 35) {
                FinalMarkup += "<tr><td class='bkgdt_col1'><span class='blacktext'>" + cmsFinalPrice + "</span></td><td class='bkgdt_col2' ><span class='blacktext'>" +
			msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span class='blacktext'>" + msg.d.FinalPrice + "</span></td></tr>";
                FinalMarkup += "<tr><td colspan='3'><span style='color: #686367;'>" + cmsPriceIncludesAll + "</span></td></tr>";
            } else {
                FinalMarkup += "<tr class='trFinalPrice'><td class='bkgdt_col1'><span>" + cmsFinalPrice + "</span></td><td class=' bkgdt_col2' ><span>" +
					msg.d.CurrencyCode + "</span></td><td class='bkgdt_col3'><span>" + msg.d.FinalPrice + "</span></td></tr>";
                FinalMarkup += "<tr class='trFinalPriceHint'><td colspan='3'><span class='priceincludes'>" + cmsPriceIncludesAll + "</span></td></tr>";
            }
        }
    }

    if ($("#finalPrice").length) {
        $("#finalPrice").append(FinalMarkup);
    }

    if (isAppliedCB || ispartAppliedCB) {
        if (!is1693) $("#pnlFinalPrice").css("padding", "10px 5px");
    }

    if (isBE3 || msg.d.IsShowLocalPrice == true) {
        if (msg.d.LocalSellingPrice != null && msg.d.LocalSellingPrice != "" && msg.d.LocalSellingPrice != "0") {
            $("#box_bkdcnote .price").append(msg.d.LocalSellingPrice);
        }
        $("#box_bkdcnote .notetext").removeClass("wauto");
        //        $("#box_bkdcnote, #box_bkdcnote .price").show();
        $("#box_bkdcnote .price").show();
        if (isBE3) {
            $("#lnkCardInfo").hide();
        }
    }

    if (FooterMarkup.length > 0) {

        $("#roomDetail").append(FooterMarkup);
    }

    $("#footerDetail").append(FinalMarkup);
    $("#pnlTotalPrice").addClass("bkgdt_marginb bg_booking final");

    if (step == 1) {
        $('#pnlTotalPrice').hide();
        if (isAppliedCB || (ispartAppliedCB && is1678))
            $('#notincluded').show();

        if (is1693) {
            if (pagetype == 32 && showcollected) {
                $('#divExcludedTaxDetail').show();
            } else {
                $('#divExcludedTaxDetail').hide();
            }
            $('#trFinalPrice').hide();
        }
    } else {
        $('#pnlTotalPrice').show();
        if (is1693) {
            if (showcollected)
                $('#divExcludedTaxDetail').show();
            else
                $('#divExcludedTaxDetail').hide();
            $('#trFinalPrice').show();
        }

        if (!is1693 && (isAppliedCB || (ispartAppliedCB && is1678)))
            $('#notincluded').hide();
    }

    AssignHoverDyn("TaxFee");
    AssignHoverDyn("TaxServiceFee");

    if (isAppliedCB || ispartAppliedCB) {
        $('.bksum-roomname .ico_qstion').hover(function () {
            $(this).css('z-index', '11');
            $(this).find('.ic-tax').addClass('ic-tax-hover').removeClass('ic-tax');
            $(this).find('.popup_body, [class^=callout]').show();
        }, function () {
            $(this).css('z-index', '10');
            $(this).find('.ic-tax-hover').addClass('ic-tax').removeClass('ic-tax-hover');
            $(this).find('.popup_body, [class^=callout]').hide();
        });
    }

    //init thickbox for 'Booking Conditions'
    tb_init('a.thickbox.bookingcond');

    //set the local amount column width
    var longestAmountStr = "";
    if (pagetype == 35 && roomratetotal.length > msg.d.FinalPrice.length) {
        longestAmountStr = roomratetotal.toString();
    } else {
        longestAmountStr = msg.d.FinalPrice.toString();
    }
    maxAmountlen = longestAmountStr.split(/[\.,\s]+/).join('').length;

    $(".bkgdt_col3").width(maxAmountlen * 9.5);

    // fix final price td width on IE6, IE7
    if (!($.browser.msie && +($.browser.version) <= 7))
        $("#footerDetail .bkgdt_col1, #finalPrice .bkgdt_col1").width($(".bkgdt_col1").eq(0).width());

    // fix ie8 width colspan bug
    if (is1678) {
        if ($.browser.msie && $.browser.version == '8.0') $('.bkgdt_col1').width((75 - maxAmountlen) + '%');
    }

    if (is1788) {
        //init modal-button
        $('#divAB1755 .modal-button, #bkg_divBooking .modal-button').each(function () {
            $(this)
            .attr('data-title', $(this).attr('popupTitle') || '')
            .attr('data-href', $(this).attr('href') || '')
            .off('click')
            .on('click', initBootstrapModal);
        });   
        //$('#bkg_divBooking .modal-button').on('click', function (e) {
        //    e.preventDefault();
        //    initBootstrapModal(e);
        //});
    }
    else {
    //Booking Condition Popup - New style
    $('a.modalpopup, area.modalpopup, input.modalpopup').click(function (e) {
        e.preventDefault();
        this.blur();
        Agoda_initialPopup(this);
        return false;
    });
    }
    //End Booking Condition Popup - New style

    if (is1693) {
        //fix ie7
        if ($.browser.msie && +($.browser.version) <= 7) {
            $('#ExcludedTaxDetail .bkgdt_col1').width($('.bkgdt_col1').eq(0).width());
            if (!isBookingCom)
                $('#tblRoomDetail .bkgdt_col1').width($('#tblRoomDetail .bkgdt_col1').width() + 5); //set width to itself to fix td width bug
        }

        //fix ie8 width colspan bug
        if ($.browser.msie && +($.browser.version) == 8) {
            if (pagetype == 35) $('.bkgdt_col1').width((75 - maxAmountlen) + '%');
            else $('#ExcludedTaxDetail .bkgdt_col1, #footerDetail .bkgdt_col1, #finalPrice .bkgdt_col1').width($('.bkgdt_col1').eq(0).width());
        }

        $('.bksum-finalprice-border').width($('.bkgdt_col2').eq(0).width() + 5 + $('.bkgdt_col3').eq(0).width());
    }

    if (is1751 && ab1751.isCurrencyChecked && step == 2 && $('#ddlIssueBankCountry:visible').length && $('#ddlChargeMeIn:visible').length) {
        ab1751.CheckIssueBankCurrency($('#ddlIssueBankCountry').val());
    }

    $('.pnlmouseoverBookCond').hover(function () {
        $(this).find('.ico_qstion').css('z-index', '11');
        $(this).find('.popup_body, [class^=callout]').show();
    }, function () {
        $(this).find('.ico_qstion').css('z-index', '10');
        $(this).find('.popup_body, [class^=callout]').hide();
    });

    $("#bkg_divBooking").show();
}

function AssignHoverDyn(obj) {
    if ($("[id^=imgIcon_" + obj + "]").size() != null || $("[id^=imgIcon_" + obj + "]").size() != 0) {
        $("[id^=imgIcon_" + obj + "]").each(function () {
            var id = this.id.replace("imgIcon_" + obj, "");
            var closeevent = function () {
                $("#div" + obj + "Popup" + id).hide();
                $("#div" + obj + "Callout" + id).hide();
            };
            //Booking Contions - dynamic Question mark icon hover show/hide popup    
            $("#imgIcon_" + obj + id + ", #lnkHover_" + obj + id).hover(
				function () {
				    var popup = $("#div" + obj + "Popup" + id).show();
				    $("#div" + obj + "Callout" + id).show();
				}, closeevent);
        });
    }
}

function GetRateDescriptionHover() {
    if (isBE3)
        return "";
    var popup_body_class = "popup_body";
    if (isBookingCom) popup_body_class = "popup_body bkdc";

    if (isAppliedCB)
        return "<div class='ico_qstion_wrapper minihover'>"
            + "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_CityTax'>"
            + "<span class='inline-block ic-tax'></span>"
            + "<div class='" + popup_body_class + "' id='divCityTaxPopup' style='display:none'>"
                + "<div class='popup_content_promotion' >" + cms.TaxText + "</div></div>"
                + "<div class='calloutDown' id='divCityTaxCallout' style='display:none'><div  class='calloutDown2'></div></div>"
                + "</div></div>"
            + "</div>";
    return "<div class='ico_qstion_wrapper'>"
            + "<div class='ico_qstion absolute'><div class='iconquestion' id='imgIcon_CityTaxUS'>"
            + "<span class='inline-block ic-tax'></span>"
            + "<div class='" + popup_body_class + "' id='divCityTaxUSPopup' style='display:none'>"
                + "<div class='popup_header_promotion' ><p><span class='inline-block sprite ic-title-popup'></span>" + TaxFeeH + "</p></div>"
                + "<div class='popup_content_promotion' >" + TaxFee + "</div></div>"
                + "<div class='calloutDown' id='divCityTaxUSCallout' style='display:none'><div  class='calloutDown2'></div></div>"
                + "</div></div>"
        + "</div>";
}                