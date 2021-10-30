# COBALT STRIKE 4.4

<p align="center">
    <img src="https://github.com/trewisscotch/CobaltStr4.4/blob/main/cobaltstrike4.4/138226901-a53c95e3-f145-498e-95cd-6a195e9f7354.png" alt="Image"  />
</p>


### Cobalt Strike is a commercial, full-featured, remote access tool that bills itself as "adversary simulation software designed to execute targeted attacks and emulate the post-exploitation actions of advanced threat actors". Cobalt Strike’s interactive post-exploit capabilities cover the full range of ATT&amp;CK tactics, all executed within a single, integrated system.

## Cobalt Strike 4.4 (August 04, 2021)
7af9c759ac78da920395debb443b9007fdf51fa66a48f0fbdaafb30b00a8a858 Cobalt Strike 4.4 Licensed (cobaltstrike.jar)

## Distribution Packages (released with Cobalt Strike 4.4)
5adf9d086a2f59be9095458f207de9e947a05696e63365a4da02acdc17caa130 Cobalt Strike MacOSX Distribution Package (20210804) 8331a77fb2f81ce969795466f8f441f02813789c24b47d0771ffdceddf8d91fe Cobalt Strike Linux Distributions Package (20210804) fdcc265fcf1d87bdfd0f7ea91138d7d9f8128f8ed157d427317619002aadd17d Cobalt Strike Windows Distribution Package (20210804)
## LAUNCH
* First you will have to unpack cobaltstrike.7z (https://github.com/)
* ./teamserver "ip_address" "password" 
  
  * IP Address - (mandatory) Enter the externally reachable IP address of the team server. Cobalt Strike uses this value as a default host for its features.
  * Password - (mandatory) Enter a password that your team members will use to connect the Cobalt Strike client to the team server.
  * Malleable C2 Profile - (optional) Specify a valid Malleable C2 Profile.
  * Kill Date - (optional) Enter a date value in YYYY-MM-DD format. The team server will embed this kill date into each Beacon stage it generates. The Beacon payload will refuse to run on or after this date and will also exit if it wakes up on or after this date.
* then Run on a different terminal : ./start.sh
* put your pass and ur username and click connect 

