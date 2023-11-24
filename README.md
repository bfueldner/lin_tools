# LIN 2.2 tools

![License](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=license&branch=main)
[![Build state](https://build.fueldner.net/badges/opensource_lin_tools.svg?branch=main)](https://build.fueldner.net/#/builders/opensource_lin_tools)
![Warnings](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=warnings&branch=main)
![Tests](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=tests&branch=main)
![Coverage](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=coverage&branch=main)

LIN 2.2 node capability file and LIN description file parser written in `boost::spirit:x3` and generator using std::stream.

## Validation

### NCF

#### Global definition

* [x] Node capability language version number

#### Node definition

* [x] General
  * [x] LIN protocol version number
  * [x] LIN product identification
  * [x] Bit rate
* [x] Diagnostic
* [x] Frame
  * [x] Frame properties
  * [x] Signal
* [x] Signal encoding type
* [x] Status management

### LDF

#### Global definition

* [x] LIN protocol version number
* [x] LIN language version number
* [x] LIN speed
* [x] Channel postfix name

#### Node definition

* [x] Participating nodes
* [x] Node attributes
* [x] Node composition

#### Signal definition

* [x] Standard signals
* [x] Diagnostic signals
* [x] Signal groups

#### Frame definition

* [x] Unconditional frames
* [x] Sporadic frames
* [x] Event triggered frames
* [x] Diagnostic frames

##### Schedule definition

* [x] Schedule table

#### Additional Information

* [x] Signal encoding type
* [x] Signal representation

---

> NON NOBIS DOMINE, NON NOBIS, SED NOMINI TUO DA GLORIAM
