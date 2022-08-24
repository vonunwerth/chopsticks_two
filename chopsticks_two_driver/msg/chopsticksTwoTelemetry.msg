float32[6] angle # rad
time startSyncTime
uint32 isrTicks # this would overflow if the robot is left on for 497 days straight at 100 hz
uint8 bufferHealth # for real-time-command-like-communication