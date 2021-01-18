char VIEW_PAGE[] = ""\
"<html>\n"\
"	<body>\n"\
"		<script type='text/javascript'>\n"\
"			var canvas = document.createElement('canvas');\n"\
"			var grafx = canvas.getContext('2d');\n"\
"			var img = document.createElement('img');\n"\
"			img_loaded = false;\n"\
"			img.style.display = 'none';\n"\
"			document.body.appendChild(canvas);\n"\
"			img.onload = function() {\n"\
"				canvas.width = img.width;\n"\
"				canvas.height = img.height;\n"\
"				grafx.drawImage(img, 0, 0);\n"\
"				img_loaded = true;\n"\
"			}\n"\
"			document.body.appendChild(img);\n"\
"			function refreshImage() {\n"\
"				img_loaded = false;\n"\
"				img.src = '/screen?time=' + new Date().getTime();\n"\
"			}\n"\
"			setInterval(function() {\n"\
"				if (img_loaded) {\n"\
"					refreshImage();\n"\
"				}\n"\
"			}, 1);\n"\
"			refreshImage();\n"\
"		</script>\n"\
"	</body>\n"\
"</html>";
