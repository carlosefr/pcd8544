/*
 * Carlos Rodrigues (c) 2010
 */


"use strict";


$(document).ready(function() {
    if (navigator.userAgent.match("MSIE\\s+[1-8]\\.")) {
        $("#editor").html("<p style=\"color: red;\">You are using an older version of Internet Explorer which isn't supported.<br>Try upgrading to a more recent <a href=\"http://www.microsoft.com/ie/\">Internet Explorer</a> version, or use another browser like <a href=\"http://firefox.com\">Firefox</a> or <a href=\"http://www.google.com/chrome/\">Chrome</a>.</p>");

        return;
    }

    // Update the C string from the graphical editor...
    $("#glyph").click(function(event) {
        var s = $("#string");

	 s.val(Processing.getInstanceById('glyph').getGlyph());
        s.removeClass("error");
    });

    // Update the graphical editor from the C string...
    $("#draw").click(function(event) {
        var s = $("#string");

        if (!Processing.getInstanceById('glyph').setGlyph(s.val())) {
            s.addClass("error");
        } else {
            s.removeClass("error");
        }
    }).click();

    // Clear the current glyph...
    $("#clear").click(function(event) {
        var s = $("#string");

        Processing.getInstanceById('glyph').clearGlyph();
        s.val("0x00, 0x00, 0x00, 0x00, 0x00");
        s.removeClass("error");
    }).click();
});


/* vim: set expandtab ts=4 sw=4: */
