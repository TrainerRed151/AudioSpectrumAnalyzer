library(tuneR)

music <- readWave("test.wav")

#s <- 90000

dx <- 32768

fs <- music@samp.rate

xx <- seq(0, dx)*fs/dx

f <- seq(5, 14)
f2 <- 2^f
ff <- f2*dx/fs + 1
fi <- floor(ff)


spectrum <- function(s) {
    ps <- fft(music@left[s:(s+dx)])
    #plot(xx, abs(ps), type="l", xlim=c(32,16384), log="xy")
    sa <- log10(abs(ps[fi]))
    print(sa)
}

for (i in seq(1, length(music@left)-dx, dx)) {
    spectrum(i)
}
