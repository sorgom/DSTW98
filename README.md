# DSTW
## the project
An implementation of an interlocking control logic (ICL) which represents the states of field elements like signals or track switches and communicates with control panels (GUIs) and the real field elements.

It consists of the following components:
- TSW: track switches
- SIG: signals
- LCR: level crossings
- SEG: track segments
- SYS: commonly used system
- COM: TCP communication to field and GUI

### goals
The project does not intend an implementation that would work in a real digital interlocking (DSTW).

The aim is to
- apply and demonstrate techniques to meet security integrity level 4 (SIL4).
- show a completely different approach than the [model driven](doc/Clinch.md) one I happened to experience.
- gain AI usage experience

## components interaction overview
![overview](doc/overview.svg)

## topics
- [SIL4](doc/SIL4.md)
- [AI usage](doc/AI.md)
- [testing](doc/testing.md)
- [transition tables](doc/transition_tables.md)
- [code coverage](doc/coverage_tools.md)
- [how to build](scripts/README.md)
- [current lines of code](doc/CLOC.md)
