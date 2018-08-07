# ft_ping

Send ICMP ECHO_REQUEST packets to network hosts

## Synopsis

```
./ft_ping [-hvqf] [-i interval] [-t ttl] host
```

## Usage

```
-h
	Display usage

-v
	Verbose output. ICMP packets other than ECHO_RESPONSE that are received are listed.

-q
	Quiet output. Nothing is displayed except the summary lines at startup time and when finished.

-f
	Flood ping. Outputs packets as fast as they come back or one hundred times per second, whichever is more.

-i interval
	Wait interval seconds between sending each packet.

-t ttl
	Set the IP Time To Live for outgoing packets.

host
	Destination host name or IP number.
```
