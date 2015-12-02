create DataHolder DataHolder0
create CUMULVS CUMULVS0
create Diffusion Diffusion0
parameters DataHolder0 CONFIG rows 10
parameters DataHolder0 CONFIG cols 10
go DataHolder0 freeze
connect Diffusion0 DATA DataHolder0 DATA
connect Diffusion0 VIZ CUMULVS0 VIZ
