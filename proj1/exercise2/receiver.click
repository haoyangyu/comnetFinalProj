
define($dev veth2)

FromDevice($dev) -> Print(Received, MAXLENGTH -1) -> Discard;
