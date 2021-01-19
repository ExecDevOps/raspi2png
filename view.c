char VIEW_PAGE[] = ""\
"<html>\n"\
"	<body>\n"\
"		<script type='text/javascript'>\n"\
"			var canvas = document.createElement('canvas');\n"\
"			canvas.__init__ = false;\n"\
"			var grafx = canvas.getContext('2d');\n"\
"			canvas.style.position = 'absolute';\n"\
"			canvas.style.top = '0px';\n"\
"			canvas.style.left = '0px';\n"\
"			canvas.style.height = '100%';\n"\
"			canvas.style.width = '100%';\n"\
"			var FULL_SCREEN = false;\n"\
"			document.body.onmouseup = function(e) {\n"\
"				FULL_SCREEN = !FULL_SCREEN;\n"\
"				if (FULL_SCREEN) {\n"\
"					document.body.requestFullscreen();\n"\
"				} else {\n"\
"					document.exitFullscreen();\n"\
"				}\n"\
"			}\n"\
"			document.body.onkeypress = function(e) {\n"\
"				switch (e.key) {\n"\
"					case '1':\n"\
"						canvas.style.width = '';\n"\
"						canvas.style.height = '';\n"\
"					break;\n"\
"					case '2':\n"\
"						canvas.style.width = '100%';\n"\
"						canvas.style.height = '';\n"\
"					break;\n"\
"					case '3':\n"\
"						canvas.style.width = '';\n"\
"						canvas.style.height = '100%';\n"\
"					break;\n"\
"					case '4':\n"\
"						canvas.style.width = '100%';\n"\
"						canvas.style.height = '100%';\n"\
"					break;\n"\
"				}\n"\
"			}\n"\
"			var img = document.createElement('img');\n"\
"			img_loaded = false;\n"\
"			img.style.display = 'none';\n"\
"			document.body.appendChild(canvas);\n"\
"			img.onload = function() {\n"\
"				if (!canvas.__init__) {\n"\
"					canvas.width = img.width;\n"\
"					canvas.height = img.height;\n"\
"					canvas.__init__ = true;"\
"				}"\
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
