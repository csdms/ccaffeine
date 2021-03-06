/* ./genlibheader analysis of /usr/local/mpich/build/LINUX/ch_p4/lib/libmpich.a -lm */
/* types are sufficient to satisfy the linker, but not 100% accurate. */
extern int MD_clock();
extern int MD_initenv();
extern int MD_initmem();
extern int MD_malloc_hint();
extern int MD_set_reference_time();
extern int MD_shfree();
extern int MD_shmalloc();
extern int data_representation();
extern int p4_error();
extern int p4_set_hard_errors();
extern int p4_soft_errors();
extern int trap_sig_errs();
extern int process_args();
extern int alloc_global();
extern int alloc_listener_info();
extern int alloc_local_bm();
extern int alloc_local_listener();
extern int alloc_local_rm();
extern int alloc_local_slave();
extern int alloc_p4_msg();
extern int free_avail_buffs();
extern int free_p4_msg();
extern int init_avail_buffs();
extern int p4_print_avail_buffs();
extern int p4_set_avail_buff();
extern int dump_conntab();
extern int dump_global();
extern int dump_listener();
extern int dump_local();
extern int dump_procgroup();
extern int dump_tmsg();
extern int p4_dprint_last();
extern int p4_dprintf();
extern int p4_dprintfl();
extern int p4_get_dbg_level();
extern int p4_set_dbg_level();
extern int print_conn_type();
extern int install_in_proctable();
extern int p4_alloc_procgroup();
extern int read_procgroup();
extern int alloc_quel();
extern int free_avail_quels();
extern int free_quel();
extern int get_tmsg();
extern int initialize_msg_queue();
extern int p4_any_messages_available();
extern int p4_messages_available();
extern int p4_msg_alloc();
extern int p4_msg_free();
extern int p4_recv();
extern int queue_p4_message();
extern int recv_message();
extern int search_p4_queue();
extern int send_message();
extern int num_in_mon_queue();
extern int p4_askfor();
extern int p4_askfor_init();
extern int p4_barrier();
extern int p4_barrier_init();
extern int p4_create();
extern int p4_getsub_init();
extern int p4_getsubs();
extern int p4_mcontinue();
extern int p4_mdelay();
extern int p4_menter();
extern int p4_mexit();
extern int p4_moninit();
extern int p4_probend();
extern int p4_progend();
extern int p4_update();
extern int p4_broadcastx();
extern int p4_dbl_absmax_op();
extern int p4_dbl_absmin_op();
extern int p4_dbl_max_op();
extern int p4_dbl_min_op();
extern int p4_dbl_mult_op();
extern int p4_dbl_sum_op();
extern int p4_flt_absmax_op();
extern int p4_flt_absmin_op();
extern int p4_flt_max_op();
extern int p4_flt_min_op();
extern int p4_flt_mult_op();
extern int p4_flt_sum_op();
extern int p4_global_op();
extern int p4_int_absmax_op();
extern int p4_int_absmin_op();
extern int p4_int_max_op();
extern int p4_int_min_op();
extern int p4_int_mult_op();
extern int p4_int_sum_op();
extern int subtree_broadcast_p4();
extern int fork_p4();
extern int get_execer_port();
extern int get_pipe();
extern int get_qualified_hostname();
extern int getswport();
extern int in_same_cluster();
extern int init_usclock();
extern int p4_accept_wait_timeout();
extern int p4_am_i_cluster_master();
extern int p4_cluster_shmem_sync();
extern int p4_get_cluster_ids();
extern int p4_get_cluster_masters();
extern int p4_get_my_cluster_id();
extern int p4_get_my_id();
extern int p4_get_my_id_from_proc();
extern int p4_global_barrier();
extern int p4_initenv();
extern int p4_machine_type();
extern int p4_num_cluster_ids();
extern int p4_num_total_ids();
extern int p4_num_total_slaves();
extern int p4_post_init();
extern int p4_proc_info();
extern int p4_shfree();
extern int p4_shmalloc();
extern int p4_usclock();
extern int p4_version();
extern int p4_wait_for_end();
extern int put_execer_port();
extern int same_data_representation();
extern int setup_conntab();
extern int zap_p4_processes();
extern int zap_remote_p4_processes();
extern int bm_start();
extern int create_bm_processes();
extern int p4_create_procgroup();
extern int p4_startup();
extern int procgroup_to_proctable();
extern int send_proc_table();
extern int sync_with_remotes();
extern int create_rm_processes();
extern int receive_proc_table();
extern int rm_start();
extern int dump_sockaddr();
extern int dump_sockinfo();
extern int get_inet_addr();
extern int get_inet_addr_str();
extern int get_sock_info_by_hostname();
extern int gethostbyname_p4();
extern int net_accept();
extern int net_conn_to_listener();
extern int net_recv();
extern int net_send();
extern int net_set_sockbuf_size();
extern int net_setup_anon_listener();
extern int net_setup_listener();
extern int p4_print_sock_params();
extern int create_remote_processes();
extern int net_create_slave();
extern int net_slave_info();
extern int p4_accept_timeout();
extern int establish_connection();
extern int handle_connection_interrupt();
extern int p4_establish_all_conns();
extern int p4_has_timedout();
extern int request_connection();
extern int send_ack();
extern int shutdown_p4_socks();
extern int sock_msg_avail_on_fd();
extern int socket_close_conn();
extern int socket_msgs_available();
extern int socket_recv();
extern int socket_recv_on_fd();
extern int socket_send();
extern int wait_for_ack();
extern int xdr_recv();
extern int xdr_send();
extern int listener();
extern int net_recv_timeout();
extern int process_connect_request();
extern int process_slave_message();
extern int getpw_ss();
extern int start_slave();
extern int shmem_msgs_available();
extern int shmem_recv();
extern int shmem_send();
extern int xx_alog_setup();
extern int xx_dump();
extern int xx_dump_aux();
extern int xx_getbuf();
extern int xx_user();
extern int xx_user1();
extern int xx_write();
extern int alogfdefine_();
extern int alogfdisable_();
extern int alogfenable_();
extern int alogflog_();
extern int alogfmaster_();
extern int alogfoutput_();
extern int alogfsetdir_();
extern int alogfsetup_();
extern int alogfstatus_();
extern int usc_MD_clock();
extern int usc_init();
extern int MPID_IrecvContig();
extern int MPID_RecvComplete();
extern int MPID_RecvContig();
extern int MPID_RecvIcomplete();
extern int MPID_BsendContig();
extern int MPID_IsendContig();
extern int MPID_SendComplete();
extern int MPID_SendContig();
extern int MPID_SendIcomplete();
extern int MPID_Abort();
extern int MPID_Complete_pending();
extern int MPID_DeviceCheck();
extern int MPID_End();
extern int MPID_Init();
extern int MPID_SetPktSize();
extern int MPID_Version_name();
extern int MPID_WaitForCompleteRecv();
extern int MPID_WaitForCompleteSend();
extern int MPID_Iprobe();
extern int MPID_Probe();
extern int MPID_IssendContig();
extern int MPID_SsendContig();
extern int MPID_IsendDatatype();
extern int MPID_SendDatatype();
extern int MPID_IrecvDatatype();
extern int MPID_RecvDatatype();
extern int MPID_Msg_act();
extern int MPID_Msg_rep();
extern int MPID_Pack();
extern int MPID_Pack_size();
extern int MPID_Unpack();
extern int MPID_PackMessage();
extern int MPID_PackMessageFree();
extern int MPID_UnpackMessageComplete();
extern int MPID_UnpackMessageSetup();
extern int MPID_IssendDatatype();
extern int MPID_SsendDatatype();
extern int MPID_BSwap_N_copy();
extern int MPID_BSwap_N_inplace();
extern int MPID_Mem_XDR_ByteDecode();
extern int MPID_Mem_XDR_ByteEncode();
extern int MPID_Mem_XDR_Decode();
extern int MPID_Mem_XDR_Decode_Logical();
extern int MPID_Mem_XDR_Encode();
extern int MPID_Mem_XDR_Encode_Logical();
extern int MPID_Mem_XDR_Free();
extern int MPID_Mem_XDR_Init();
extern int MPID_Mem_XDR_Len();
extern int MPID_Mem_convert_len();
extern int MPID_Type_XDR_decode();
extern int MPID_Type_XDR_encode();
extern int MPID_Type_swap_copy();
extern int MPID_Type_swap_inplace();
extern int MPID_Request_free();
extern int MPID_RecvCancel();
extern int MPID_SendCancel();
extern int MPID_CH_Eagerb_cancel_send();
extern int MPID_CH_Eagerb_delete();
extern int MPID_CH_Eagerb_irecv();
extern int MPID_CH_Eagerb_isend();
extern int MPID_CH_Eagerb_recv();
extern int MPID_CH_Eagerb_save();
extern int MPID_CH_Eagerb_send();
extern int MPID_CH_Eagerb_setup();
extern int MPID_CH_Eagerb_unxrecv_start();
extern int MPID_CH_Rndvb_ack();
extern int MPID_CH_Rndvb_delete();
extern int MPID_CH_Rndvb_irecv();
extern int MPID_CH_Rndvb_isend();
extern int MPID_CH_Rndvb_ok_to_send();
extern int MPID_CH_Rndvb_save();
extern int MPID_CH_Rndvb_save_self();
extern int MPID_CH_Rndvb_send();
extern int MPID_CH_Rndvb_setup();
extern int MPID_CH_Rndvb_unxrecv_end();
extern int MPID_CH_Rndvb_unxrecv_start();
extern int MPID_CH_Rndvb_unxrecv_start_self();
extern int MPID_CH_Rndvb_unxrecv_test_end();
extern int MPID_GetMsgDebugFlag();
extern int MPID_Get_print_pkt();
extern int MPID_PrintMsgDebug();
extern int MPID_Print_Send_Handle();
extern int MPID_Print_mode();
extern int MPID_Print_packet();
extern int MPID_Print_pkt_data();
extern int MPID_Print_rhandle();
extern int MPID_Print_shandle();
extern int MPID_Rndv_print_pkt();
extern int MPID_SetDebugFile();
extern int MPID_SetDebugFlag();
extern int MPID_SetMsgDebugFlag();
extern int MPID_SetSpaceDebugFlag();
extern int MPID_Set_tracefile();
extern int MPID_CH_Check_incoming();
extern int MPID_CH_Eagerb_isend_short();
extern int MPID_CH_Eagerb_recv_short();
extern int MPID_CH_Eagerb_save_short();
extern int MPID_CH_Eagerb_send_short();
extern int MPID_CH_Eagerb_short_delete();
extern int MPID_CH_Eagerb_unxrecv_start_short();
extern int MPID_CH_Short_setup();
extern int MPID_FlowDebug();
extern int MPID_FlowDelete();
extern int MPID_FlowDump();
extern int MPID_FlowSetup();
extern int MPID_RecvFlowPacket();
extern int MPID_SendFlowPacket();
extern int MPID_CH_Abort();
extern int MPID_CH_End();
extern int MPID_CH_InitMsgPass();
extern int MPID_CH_Version_name();
extern int MPID_Node_name();
extern int MPID_ByteSwapInt();
extern int MPID_CH_Comm_msgrep();
extern int MPID_CH_Hetero_free();
extern int MPID_CH_Init_hetero();
extern int MPID_CH_Pkt_pack();
extern int MPID_CH_Pkt_unpack();
extern int MPID_GetByteOrder();
extern int MPID_CH_Wtick();
extern int MPID_P4_End();
extern int MPID_P4_Init();
extern int MPID_Dequeue();
extern int MPID_Dump_queue();
extern int MPID_Dump_queues();
extern int MPID_Enqueue();
extern int MPID_InitQueue();
extern int MPID_Msg_arrived();
extern int MPID_Search_posted_queue();
extern int MPID_Search_unexpected_queue();
extern int MPID_Search_unexpected_queue_and_post();
extern int MPID_ArgSqueeze();
extern int MPID_GetIntParameter();
extern int MPID_ProcessArgs();
extern int MPID_TrSetMaxMem();
extern int MPID_trDebugLevel();
extern int MPID_trImerge();
extern int MPID_trIsort();
extern int MPID_trSortBlocks();
extern int MPID_trSummary();
extern int MPID_trcalloc();
extern int MPID_trdump();
extern int MPID_trdumpGrouped();
extern int MPID_trfree();
extern int MPID_trid();
extern int MPID_trinit();
extern int MPID_trlevel();
extern int MPID_trmalloc();
extern int MPID_trpop();
extern int MPID_trpush();
extern int MPID_trrealloc();
extern int MPID_trspace();
extern int MPID_trvalid();
extern int MPID_SBDump();
extern int MPID_SBFlush();
extern int MPID_SBPrealloc();
extern int MPID_SBReleaseAvail();
extern int MPID_SBalloc();
extern int MPID_SBdestroy();
extern int MPID_SBfree();
extern int MPID_SBiAllocate();
extern int MPID_SBinit();
extern int MPID_SBrelease();
extern int MPID_SBvalid();
extern int MPIR_Ref_init();
extern int TR_stack_init();
extern int MPI_Isend();
extern int MPI_Irecv();
extern int MPI_Wait();
extern int MPI_Test();
extern int MPIR_Error();
extern int MPIR_Errors_are_fatal();
extern int MPIR_Errors_return();
extern int MPIR_Errors_warn();
extern int MPIR_Set_Status_error_array();
extern int MPI_Address();
extern int MPI_Cancel();
extern int MPI_Request_free();
extern int MPI_Probe();
extern int MPI_Start();
extern int MPI_Testany();
extern int MPI_Waitall();
extern int MPI_Send();
extern int MPI_Recv();
extern int MPI_Sendrecv();
extern int MPI_Iprobe();
extern int MPI_Testall();
extern int MPI_Waitany();
extern int MPI_Recv_init();
extern int MPI_Send_init();
extern int MPI_Sendrecv_replace();
extern int MPI_Get_count();
extern int MPI_Bsend();
extern int MPI_Ssend();
extern int MPI_Rsend();
extern int MPI_Buffer_attach();
extern int MPI_Buffer_detach();
extern int MPI_Ibsend();
extern int MPI_Issend();
extern int MPI_Irsend();
extern int MPI_Waitsome();
extern int MPI_Testsome();
extern int MPI_Test_cancelled();
extern int MPI_Bsend_init();
extern int MPI_Rsend_init();
extern int MPI_Ssend_init();
extern int MPI_Startall();
extern int MPI_Type_commit();
extern int MPI_Type_contiguous();
extern int MPI_Type_extent();
extern int MPI_Type_free();
extern int MPI_Type_hindexed();
extern int MPI_Type_hvector();
extern int MPI_Type_indexed();
extern int MPI_Type_lb();
extern int MPI_Type_size();
extern int MPI_Type_struct();
extern int MPI_Type_ub();
extern int MPIR_Datatype_iscontig();
extern int MPIR_Free_perm_type();
extern int MPIR_Free_struct_internals();
extern int MPIR_Type_dup();
extern int MPIR_Type_free();
extern int MPIR_Type_get_limits();
extern int MPIR_Type_permanent();
extern int MPI_Type_vector();
extern int MPI_Get_elements();
extern int MPI_Pack_size();
extern int MPI_Pack();
extern int MPI_Unpack();
extern int mpi_isend__();
extern int mpi_irecv__();
extern int mpi_wait__();
extern int mpi_test__();
extern int mpi_address__();
extern int mpi_cancel__();
extern int mpi_request_free__();
extern int mpi_probe__();
extern int mpi_start__();
extern int mpi_testany__();
extern int mpi_waitall__();
extern int mpi_send__();
extern int mpi_recv__();
extern int mpi_sendrecv__();
extern int mpi_iprobe__();
extern int mpi_testall__();
extern int mpi_waitany__();
extern int mpi_recv_init__();
extern int mpi_send_init__();
extern int mpi_sendrecv_replace__();
extern int mpi_get_count__();
extern int mpi_bsend__();
extern int mpi_ssend__();
extern int mpi_rsend__();
extern int mpi_buffer_attach__();
extern int mpi_buffer_detach__();
extern int mpi_ibsend__();
extern int mpi_issend__();
extern int mpi_irsend__();
extern int mpi_waitsome__();
extern int mpi_testsome__();
extern int mpi_test_cancelled__();
extern int mpi_bsend_init__();
extern int mpi_rsend_init__();
extern int mpi_ssend_init__();
extern int mpi_startall__();
extern int mpi_type_commit__();
extern int mpi_type_contiguous__();
extern int mpi_type_extent__();
extern int mpi_type_free__();
extern int mpi_type_hindexed__();
extern int mpi_type_hvector__();
extern int mpi_type_indexed__();
extern int mpi_type_lb__();
extern int mpi_type_size__();
extern int mpi_type_struct__();
extern int mpi_type_ub__();
extern int mpi_type_vector__();
extern int mpi_get_elements__();
extern int mpi_pack_size__();
extern int mpi_pack__();
extern int mpi_unpack__();
extern int MPI_Abort();
extern int MPIR_Breakpoint();
extern int MPI_Init();
extern int MPIR_Errhandler_create();
extern int MPIR_Errhandler_mark();
extern int MPIR_Init();
extern int mpir_init_bottom__();
extern int MPI_Finalize();
extern int MPI_Initialized();
extern int MPI_Error_string();
extern int MPIR_cstr2fstr();
extern int MPIR_fstr2cstr();
extern int MPIR_Free_dtes();
extern int MPIR_Init_dtes();
extern int MPIR_Setup_base_datatype();
extern int MPIR_Setup_complex_datatype();
extern int MPIR_Type_contiguous();
extern int mpir_init_fsize__();
extern int MPI_Get_processor_name();
extern int MPI_Errhandler_create();
extern int MPI_Errhandler_set();
extern int MPI_Errhandler_get();
extern int MPI_Errhandler_free();
extern int MPI_Error_class();
extern int MPI_Wtime();
extern int MPI_Wtick();
extern int MPIR_GetErrorMessage();
extern int MPIR_GetNLSMsg();
extern int MPI_Get_version();
extern int MPIR_Msg_queue_export();
extern int mpi_initialized__();
extern int mpi_abort__();
extern int mpi_finalize__();
extern int mpi_error_string__();
extern int mpi_get_processor_name__();
extern int mpi_errhandler_create__();
extern int mpi_errhandler_set__();
extern int mpi_errhandler_get__();
extern int mpi_errhandler_free__();
extern int mpi_error_class__();
extern int mpi_wtime__();
extern int mpi_wtick__();
extern int mpi_get_version__();
extern int mpir_init_fcm__();
extern int mpir_init_flog__();
extern int mpir_get_fsize__();
extern int mpir_init_fdtes__();
extern int MPE_GetHostName();
extern int MPIR_HvectorLen();
extern int MPIR_Pack_Hvector();
extern int MPIR_UnPack_Hvector();
extern int MPIR_Elementcnt();
extern int MPIR_Pack2();
extern int MPIR_PrintDatatypePack();
extern int MPIR_PrintDatatypeUnpack();
extern int MPIR_Printcontig();
extern int MPIR_Printcontig2();
extern int MPIR_Printcontig2a();
extern int MPIR_Unpack();
extern int MPIR_Unpack2();
extern int MPIR_HBT_Free();
extern int MPIR_HBT_Init();
extern int MPIR_HBT_delete();
extern int MPIR_HBT_free_node();
extern int MPIR_HBT_free_subtree();
extern int MPIR_HBT_free_tree();
extern int MPIR_HBT_insert();
extern int MPIR_HBT_lookup();
extern int MPIR_HBT_new_node();
extern int MPIR_HBT_new_tree();
extern int MPIR_Tab();
extern int MPIR_dump_dte();
extern int MPIR_DestroyPointer();
extern int MPIR_DumpPointers();
extern int MPIR_FromPointer();
extern int MPIR_PointerOpts();
extern int MPIR_PointerPerm();
extern int MPIR_RegPointerIdx();
extern int MPIR_RmPointer();
extern int MPIR_ToPointer();
extern int MPIR_UsePointer();
extern int MPIR_BsendAlloc();
extern int MPIR_BsendCopyData();
extern int MPIR_BsendFreeReq();
extern int MPIR_BsendInitBuffer();
extern int MPIR_BsendPersistent();
extern int MPIR_BsendRelease();
extern int MPIR_IbsendDatatype();
extern int MPIR_MergeBlock();
extern int MPI_Keyval_free();
extern int MPI_Keyval_create();
extern int MPI_Attr_get();
extern int MPI_Attr_delete();
extern int MPIR_Attr_copy();
extern int MPIR_Attr_copy_node();
extern int MPIR_Attr_copy_subtree();
extern int MPIR_Attr_create_tree();
extern int MPIR_Attr_dup_tree();
extern int MPIR_Attr_free_node();
extern int MPIR_Attr_free_subtree();
extern int MPIR_Attr_free_tree();
extern int MPIR_Attr_make_perm();
extern int MPIR_Keyval_create();
extern int MPI_Attr_put();
extern int MPI_Group_excl();
extern int MPI_Group_difference();
extern int MPI_Group_free();
extern int MPI_Group_incl();
extern int MPI_Group_intersection();
extern int MPI_Group_range_excl();
extern int MPI_Group_range_incl();
extern int MPI_Group_compare();
extern int MPI_Group_rank();
extern int MPI_Group_size();
extern int MPI_Group_union();
extern int MPIR_CreateGroup();
extern int MPIR_Dump_group();
extern int MPIR_Dump_ranges();
extern int MPIR_Dump_ranks();
extern int MPIR_FreeGroup();
extern int MPIR_Group_N2_prev();
extern int MPIR_Powers_of_2();
extern int MPIR_SetToIdentity();
extern int MPI_Comm_dup();
extern int MPI_Comm_free();
extern int MPI_Comm_group();
extern int MPI_Comm_create();
extern int MPI_Comm_rank();
extern int MPI_Comm_get_name();
extern int MPI_Comm_set_name();
extern int MPI_Comm_size();
extern int MPIR_Comm_N2_prev();
extern int MPIR_Comm_collops_init();
extern int MPIR_Comm_forget();
extern int MPIR_Comm_init();
extern int MPIR_Comm_make_coll();
extern int MPIR_Comm_remember();
extern int MPIR_Dump_comm();
extern int MPIR_Intercomm_high();
extern int MPIR_Sort_split_table();
extern int MPI_Comm_split();
extern int MPIR_Context_alloc();
extern int MPIR_Context_dealloc();
extern int MPI_Group_translate_ranks();
extern int MPI_Comm_test_inter();
extern int MPI_Comm_compare();
extern int MPI_Comm_remote_size();
extern int MPI_Comm_remote_group();
extern int MPI_Intercomm_create();
extern int MPI_Intercomm_merge();
extern int mpi_group_range_incl__();
extern int mpi_group_range_excl__();
extern int MPIR_null_copy_fn();
extern int MPIR_null_delete_fn();
extern int MPIR_dup_fn();
extern int mpi_keyval_free__();
extern int mpi_keyval_create__();
extern int mpi_attr_get__();
extern int mpi_attr_delete__();
extern int mpi_attr_put__();
extern int mpi_group_excl__();
extern int mpi_group_difference__();
extern int mpi_group_free__();
extern int mpi_group_incl__();
extern int mpi_group_intersection__();
extern int mpi_group_rank__();
extern int mpi_group_size__();
extern int mpi_group_union__();
extern int mpi_group_compare__();
extern int mpi_comm_dup__();
extern int mpi_comm_free__();
extern int mpi_comm_group__();
extern int mpi_comm_create__();
extern int mpi_comm_set_name__();
extern int mpi_comm_get_name__();
extern int mpi_comm_size__();
extern int mpi_comm_split__();
extern int mpi_group_translate_ranks__();
extern int mpi_comm_test_inter__();
extern int mpi_comm_rank__();
extern int mpi_comm_compare__();
extern int mpi_comm_remote_size__();
extern int mpi_comm_remote_group__();
extern int mpi_intercomm_create__();
extern int mpi_intercomm_merge__();
extern int mpi_null_copy_fn__();
extern int mpi_null_delete_fn__();
extern int mpi_dup_fn__();
extern int MPI_Barrier();
extern int MPI_Bcast();
extern int MPI_Gather();
extern int MPI_Gatherv();
extern int MPI_Scatter();
extern int MPI_Scatterv();
extern int MPI_Allgather();
extern int MPI_Allgatherv();
extern int MPI_Alltoall();
extern int MPI_Alltoallv();
extern int MPI_Reduce();
extern int MPI_Allreduce();
extern int MPI_Reduce_scatter();
extern int MPI_Scan();
extern int MPIR_BAND();
extern int MPIR_BOR();
extern int MPIR_BXOR();
extern int MPIR_LAND();
extern int MPIR_LOR();
extern int MPIR_LXOR();
extern int MPIR_MAXF();
extern int MPIR_MAXLOC();
extern int MPIR_MINF();
extern int MPIR_MINLOC();
extern int MPIR_PROD();
extern int MPIR_SUM();
extern int MPI_Op_create();
extern int MPI_Op_free();
extern int MPIR_Op_setup();
extern int mpi_barrier__();
extern int mpi_bcast__();
extern int mpi_gather__();
extern int mpi_gatherv__();
extern int mpi_scatter__();
extern int mpi_scatterv__();
extern int mpi_allgather__();
extern int mpi_allgatherv__();
extern int mpi_alltoall__();
extern int mpi_alltoallv__();
extern int mpi_reduce__();
extern int mpi_allreduce__();
extern int mpi_reduce_scatter__();
extern int mpi_scan__();
extern int mpi_op_create__();
extern int mpi_op_free__();
extern int MPI_Topo_test();
extern int MPI_Graphdims_get();
extern int MPI_Graph_get();
extern int MPI_Cartdim_get();
extern int MPI_Cart_get();
extern int MPIR_root();
extern int MPI_Dims_create();
extern int MPI_Cart_map();
extern int MPI_Graph_map();
extern int MPI_Cart_create();
extern int MPI_Graph_create();
extern int MPI_Cart_rank();
extern int MPI_Cart_coords();
extern int MPI_Graph_neighbors_count();
extern int MPI_Graph_neighbors();
extern int MPI_Cart_shift();
extern int MPI_Cart_sub();
extern int MPIR_Topology_Free();
extern int MPIR_Topology_Init();
extern int MPIR_Topology_copy_fn();
extern int MPIR_Topology_delete_fn();
extern int MPIR_Topology_finalize();
extern int MPIR_Topology_init();
extern int mpi_topo_test__();
extern int mpi_graphdims_get__();
extern int mpi_graph_get__();
extern int mpi_cartdim_get__();
extern int mpi_cart_get__();
extern int mpi_dims_create__();
extern int mpi_cart_map__();
extern int mpi_graph_map__();
extern int mpi_cart_create__();
extern int mpi_graph_create__();
extern int mpi_cart_rank__();
extern int mpi_cart_coords__();
extern int mpi_graph_neighbors_count__();
extern int mpi_graph_neighbors__();
extern int mpi_cart_shift__();
extern int mpi_cart_sub__();
extern int MPI_Pcontrol();
extern int mpi_pcontrol__();
extern int MPI_Finalized();
extern int MPI_Request_c2f();
extern int MPI_Status_c2f();
extern int MPI_Status_f2c();
extern int MPI_Type_create_indexed_block();
extern int MPI_Type_create_subarray();
extern int MPIOI_Type_block();
extern int MPIOI_Type_cyclic();
extern int MPI_Type_create_darray();
extern int MPI_Info_create();
extern int MPI_Info_dup();
extern int MPI_Info_get();
extern int MPI_Info_get_nthkey();
extern int MPI_Info_set();
extern int MPI_Info_delete();
extern int MPI_Info_free();
extern int MPI_Info_get_nkeys();
extern int MPI_Info_get_valuelen();
extern int MPI_Info_c2f();
extern int MPI_Info_f2c();
extern int mpi_finalized__();
extern int mpi_type_create_indexed_block__();
extern int mpi_type_create_subarray__();
extern int mpi_type_create_darray__();
extern int mpi_info_create__();
extern int mpi_info_dup__();
extern int mpi_info_get__();
extern int mpi_info_get_nthkey__();
extern int mpi_info_set__();
extern int mpi_info_delete__();
extern int mpi_info_free__();
extern int mpi_info_get_nkeys__();
extern int mpi_info_get_valuelen__();
extern int MPI_Type_get_contents();
extern int MPI_Type_get_envelope();
extern int mpi_type_get_contents__();
extern int mpi_type_get_envelope__();
