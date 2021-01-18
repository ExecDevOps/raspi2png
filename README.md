# raspi2png

Utility to take a snapshot of the raspberry pi screen and save it as a PNG file

Modified fork to allow streaming. The streams can be viewed from any computer on the local network in the web browser. This is just an experiment. Framerate is rather low. See the video below. Scaling down the resolution seems to speed up the framerate but of course at quality loss. While you can view the stream at /view, the direct images themselves are uploaded at /screen. Making a separate program to view them that runs natively and not in the browser might see better framerates. In the future I would like to also update this to allow controlling the Pi through the browser as well.


    Usage: raspi2png [--pngname name] [--width <width>] [--height <height>] [--compression <level>] [--delay <delay>] [--display <number>] [--stdout] [--help]

    --pngname,-p - name of png file to create (default is snapshot.png)
    --height,-h - image height (default is screen height)
    --width,-w - image width (default is screen width)
    --compression,-c - PNG compression level (0 - 9)
    --delay,-d - delay in seconds (default 0)
    --display,-D - Raspberry Pi display number (default 0)
	--stdout,-s - write file to stdout
    --help,-H - print this usage information

    Streaming usage:
         Stream the contents of the screen to the web browser at http://ip_address:port_number/view

         raspi2png stream - Start a stream on port 8888
         raspi2png stream [port] - Start a stream on port [port]
         raspi2png stream [port] [scale] - Scale the resolution by a factor
         raspi2png stop - Stop a running stream

## Simple Install

Run this command through terminal or CLI screen.

curl -sL https://raw.githubusercontent.com/AndrewFromMelbourne/raspi2png/master/installer.sh | bash -

## Manual Building

You will need to install libpng before you build the program. On Raspbian

sudo apt-get install libpng12-dev

Then just type 'make' in the raspi2png directory you cloned from github.

