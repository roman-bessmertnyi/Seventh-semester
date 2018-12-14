$(function () {
    $( "#forward" ).on('touchstart mousedown', function(e) {
        e.preventDefault();
		var t = $("#pathCanvas").offset().top;
		var l = $("#pathCanvas").offset().left;
        $("#pathCanvas").offset({ top: t - 100, left: l });
    });

    $( "#left" ).on('touchstart mousedown', function(e) {
        e.preventDefault();
        var t = $("#pathCanvas").offset().top;
		var l = $("#pathCanvas").offset().left;
        $("#pathCanvas").offset({ top: t , left: l - 100 });
    });

    $( "#right" ).on('touchstart mousedown', function(e) {
        e.preventDefault();
        var t = $("#pathCanvas").offset().top;
		var l = $("#pathCanvas").offset().left;
        $("#pathCanvas").offset({ top: t, left: l + 100 });
    });

    $( "#back" ).on('touchstart mousedown', function(e) {
        e.preventDefault();
        var t = $("#pathCanvas").offset().top;
		var l = $("#pathCanvas").offset().left;
        $("#pathCanvas").offset({ top: t + 100, left: l });
    });
});