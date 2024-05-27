#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*****************  Standard Types ***************/

typedef unsigned char		u8	;
typedef signed	 char		s8	;

typedef unsigned short		u16	;
typedef signed	 short		s16	;

typedef unsigned int		u32	;
typedef signed	 int		s32	;

typedef unsigned long long	u64	;
typedef signed	 long long	s64	;

typedef float				f32	;
typedef double				f64	;

/*****************  definitions ***************/

#define NULL 		(void *)0



typedef enum{
	E_OK,
	E_NOK,
	E_NOK_NULL_PTR,
	E_NOK_OUT_OF_RANGE,
	E_NOK_BUSY
}ReturnType_State_t;

typedef enum{
	FALSE=0,
	TRUE = !FALSE
}Bool_t;

typedef enum{
	IDLE,
	BUSY
}Module_State_t;

typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef void(* PtrToFunc_void)(void);




#endif /* STD_TYPES_H_ */
