# palmak
## A simple and lightweight palette maker

(currently *nix only)

# Features
- True color support
- Simple CLI interface
- Easily scriptable

# Basic usage

https://github.com/mid-at-coding/palmak/assets/64973075/8f8240c1-0635-4512-89ad-74fe23fe4da4


palmak { hex | hsv } [ options ]

## Options

help - get, well, help

h / hex - input a base color in hex (e.g. palmak h FFFFFF)

c / count - input the width of the palette, or how many colors there are in both sides from the base color (default: 2)

hs / hueshift - the amount to shift the hue of the color, in degrees (default: 9)

vs / valueshift - the amount to shift the value of the color, in % (default: -10%)

ss / satshift - the amount to shift the saturation of the color, in % (default: 0%)

nc / nocolor - disable color output

nt / notext - disable text output

v / verbose - enable debug output
