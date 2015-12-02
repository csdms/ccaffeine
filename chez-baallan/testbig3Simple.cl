create TextView TextView0
create Identity_PC Identity_PC0
create DataHolder DataHolder0
create Diffusion2 Diffusion20
create ISIS_GMRES ISIS_GMRES0
create ISIS_Vector ISIS_Vector0
create ISIS_DCSR_Matrix ISIS_DCSR_Matrix0
parameters DataHolder0 CONFIG rows 10
parameters DataHolder0 CONFIG cols 10
go DataHolder0 freeze
connect ISIS_Vector0 ESI_MapPartition DataHolder0 map
connect Diffusion20 DATA DataHolder0 DATA
connect ISIS_DCSR_Matrix0 ESI_MapPartition DataHolder0 map
connect Diffusion20 matrixRowBuilder ISIS_DCSR_Matrix0 ESI_MatrixRowBuilder
go Diffusion20 setupMatrix
go ISIS_DCSR_Matrix0 freezeRows
connect Diffusion20 matrixPutRow ISIS_DCSR_Matrix0 ESI_MatrixRowWriteAccess

connect Identity_PC0 Sample_ESI_Vector ISIS_Vector0 x
connect Identity_PC0 ESI_MatrixMultiply ISIS_DCSR_Matrix0 ESI_MatrixMultiply
connect ISIS_GMRES0 ESI_Operator ISIS_DCSR_Matrix0 ESI_Operator
connect ISIS_GMRES0 ESI_Preconditioner Identity_PC0 ESI_Preconditioner

connect Diffusion20 BVector ISIS_Vector0 x
parameters Diffusion20 Config timeParam 0.1
parameters Diffusion20 Config dxParam 0.1
parameters Diffusion20 Config dyParam 0.1
parameters Diffusion20 Config dtParam 0.1
parameters Diffusion20 Config tEndParam 50.0
parameters Diffusion20 Config tBeginParam 1.0
parameters Diffusion20 Config isRandom true
parameters Diffusion20 Config randDuration 30.0
parameters Diffusion20 Config randProbability 0.0080
parameters Diffusion20 Config randMaxTemp 100000.0
parameters Diffusion20 Config randMinTemp 1.0
connect Diffusion20 ESI_Solver ISIS_GMRES0 ESI_Solver
connect Diffusion20 Viz TextView0 VIZ
 
go Diffusion20 Go
