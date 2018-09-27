.name "omegabot"
.comment "no comments"

o:
    st  r1,  120
    ld  %1,   r2
    st  r2,  104
    live    %120
    st  r1,  -120
    ld  %1,   r2
    st  r2,  -136
    live    %-120
    ld  %0, r3

x:
    st  r1,  1200
    ld  %1,   r2
    st  r2,  1184
    live    %120
    st  r1,  -2200
    ld  %1,   r2
    st  r2,  -2216
    live    %-120
    ld  %0, r3
    zjmp    %:o
