#ifndef WINLIST_WINDATA_H_HEADER_INCLUDED
#define WINLIST_WINDATA_H_HEADER_INCLUDED

typedef struct ASWindowData
{
#define MAGIC_ASWindowData	0xA3817D08
	unsigned long magic ;
	Window 	client;
	Window 	frame ;
	
	unsigned long 	ref_ptr ; /* address of the related ASWindow structure in 
	                             afterstep's own memory space - we use it as a 
							     reference, to know what object change is related to */
	ASRectangle 	frame_rect ;
	int 			desk ;
	unsigned long 	flags ;
	int 			tbar_height ;
	int 			sbar_height ; /* misteriously called boundary_width in 
	                                 afterstep proper for no apparent reason */
	XSizeHints 		hints ; 	  /* not sure why we need it here */
	
	Window 			icon_title ;
	Window          icon ;									 
	
	ARGB32 			fore, back ;  /* really is kinda useless here */
	
	char 			*window_name ;
	char 			*icon_name ;
	char 			*res_class ;
	char 			*res_name ;
	
	ASRectangle      icon_rect ;
	
	Bool 			 focused ;
	Bool			 iconic ;
	
	void *data ;
	
}ASWindowData;
/**********************************************************************/
/* w, frame, t and the rest of the full window config */
#define WINDOW_CONFIG_MASK (M_ADD_WINDOW|M_CONFIGURE_WINDOW)
/* w, frame, t, icon_p_x, icon_p_y, icon_p_width, icon_p_height :*/
#define WINDOW_ICON_MASK   (M_ICONIFY|M_DEICONIFY)
/* w, frame, t, and then text :*/
#define WINDOW_NAME_MASK   (M_WINDOW_NAME|M_ICON_NAME|M_RES_CLASS|M_RES_NAME)
/* w, frame and t */
#define WINDOW_STATE_MASK  (M_FOCUS_CHANGE|M_DESTROY_WINDOW)

#define WINDOW_PACKET_MASK (WINDOW_CONFIG_MASK|WINDOW_ICON_MASK| \
                            WINDOW_NAME_MASK|WINDOW_STATE_MASK)

typedef enum { 
	WP_Error = -1,
	WP_Handled,
	WP_DataCreated,
	WP_DataChanged,
	WP_DataDeleted
}WindowPacketResult ;

void destroy_window_data(ASWindowData *wd);
ASWindowData *fetch_window_by_id( Window w );
ASWindowData *add_window_data( ASWindowData *wd );
WindowPacketResult handle_window_packet(unsigned long type, unsigned long *data, ASWindowData **pdata);

#endif /* #ifndef WINLIST_WINDATA_H_HEADER_INCLUDED */