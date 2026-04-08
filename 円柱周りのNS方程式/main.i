# 0 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c"







# 1 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 1 3
# 9 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/corecrt_stdio_config.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/corecrt_stdio_config.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 1 3
# 108 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3
             
# 117 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3
             
# 326 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3
       
# 405 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3
       
# 11 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_secapi.h" 1 3
# 12 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3
# 306 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 1 3
# 9 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3
# 685 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/sdks/_mingw_ddk.h" 1 3
# 686 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 24 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3
  
# 24 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3
 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "C:/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3
#pragma pack(pop)
# 307 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3
# 604 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{



  __asm__ __volatile__("int {$}3":);





}
# 625 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code)
{




  __asm__ __volatile__("int {$}0x29"::"c"(code));






  __builtin_unreachable();
}
# 665 "C:/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3
const char *__mingw_get_crt_info (void);
# 11 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 35 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
__extension__ typedef unsigned long long size_t;
# 45 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 62 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
__extension__ typedef long long intptr_t;
# 75 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 88 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
__extension__ typedef long long ptrdiff_t;
# 98 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 138 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
typedef __time64_t time_t;
# 430 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {





  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;

} threadlocinfo;
# 501 "C:/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3
#pragma pack(pop)
# 11 "C:/mingw64/x86_64-w64-mingw32/include/corecrt_stdio_config.h" 2 3





unsigned long long* __attribute__((__cdecl__)) __local_stdio_printf_options(void);
unsigned long long* __attribute__((__cdecl__)) __local_stdio_scanf_options(void);
# 10 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 2 3

#pragma pack(push,_CRT_PACKING)

       

       

       

       
# 33 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  struct _iobuf {



    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;

  };
  typedef struct _iobuf FILE;
# 99 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_off_t.h" 1 3




  typedef long _off_t;

  typedef long off32_t;





  __extension__ typedef long long _off64_t;

  __extension__ typedef long long off64_t;
# 26 "C:/mingw64/x86_64-w64-mingw32/include/_mingw_off_t.h" 3
typedef off32_t off_t;
# 100 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 2 3

__attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __acrt_iob_func(unsigned index);

  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __iob_func(void);
# 112 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __extension__ typedef long long fpos_t;
# 156 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
extern
  __attribute__((__format__(__gnu_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__gnu_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsscanf (const char * __restrict__ _Str,const char * __restrict__ Format,va_list argp);
extern
  __attribute__((__format__(__gnu_scanf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_scanf(const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__gnu_scanf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vscanf(const char * __restrict__ Format, va_list argp);
extern
  __attribute__((__format__(__gnu_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__gnu_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfscanf (FILE * __restrict__ fp, const char * __restrict__ Format,va_list argp);

extern
  __attribute__((__format__(__gnu_printf__,3,0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnprintf(char * __restrict__ _DstBuf,size_t _MaxCount,const char * __restrict__ _Format,
                               va_list _ArgList);
extern
  __attribute__((__format__(__gnu_printf__,3,4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snprintf(char * __restrict__ s, size_t n, const char * __restrict__ format, ...);
extern
  __attribute__((__format__(__gnu_printf__,1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_printf(const char * __restrict__ , ... ) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vprintf (const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fprintf (FILE * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sprintf (char * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsprintf (char * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,3))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_asprintf(char ** __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__gnu_printf__,2,0))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_vasprintf(char ** __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));

extern
  __attribute__((__format__(__ms_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...)
  ;
extern
  __attribute__((__format__(__ms_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vsscanf(const char * __restrict__ _Str,const char * __restrict__ _Format,va_list argp)
  __asm__("vsscanf");
extern
  __attribute__((__format__(__ms_scanf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_scanf(const char * __restrict__ _Format,...)
  ;
extern
  __attribute__((__format__(__ms_scanf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vscanf(const char * __restrict__ _Format,va_list argp)
  __asm__("vscanf");
extern
  __attribute__((__format__(__ms_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...)
  ;
extern
  __attribute__((__format__(__ms_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,va_list argp)
  __asm__("vfscanf");

extern
  __attribute__((__format__(__ms_printf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_printf(const char * __restrict__ , ... )
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vprintf (const char * __restrict__ , va_list)
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fprintf (FILE * __restrict__ , const char * __restrict__ , ...)
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list)
  __attribute__ ((__nothrow__))
;
extern
  __attribute__((__format__(__ms_printf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sprintf (char * __restrict__ , const char * __restrict__ , ...)
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vsprintf (char * __restrict__ , const char * __restrict__ , va_list)
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 3,4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_snprintf (char * __restrict__ , size_t , const char * __restrict__ , ...)
  __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__ms_printf__, 3,0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vsnprintf (char * __restrict__ , size_t , const char * __restrict__ , va_list)
  __attribute__ ((__nothrow__));
# 308 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
__attribute__((__format__(__gnu_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
int sscanf(const char *__source, const char *__format, ...)
__asm__("__mingw_sscanf");

__attribute__((__format__(__gnu_scanf__, 1,2))) __attribute__ ((__nonnull__ (1)))
int scanf(const char *__format, ...)
__asm__("__mingw_scanf");

__attribute__((__format__(__gnu_scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
int fscanf(FILE *__stream, const char *__format, ...)
__asm__("__mingw_fscanf");



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"


__attribute__((__format__(__gnu_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
int vsscanf (const char *__source, const char *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vsscanf");

__attribute__((__format__(__gnu_scanf__, 1,0))) __attribute__ ((__nonnull__ (1)))
int vscanf(const char *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vscanf");

__attribute__((__format__(__gnu_scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
int vfscanf (FILE *__stream, const char *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vfscanf");


#pragma GCC diagnostic pop





__attribute__((__format__(__gnu_printf__,2,3))) __attribute__ ((__nonnull__ (2)))
int fprintf (FILE *__stream, const char *__format, ...)
__asm__("__mingw_fprintf");

__attribute__((__format__(__gnu_printf__,1,2))) __attribute__ ((__nonnull__ (1)))
int printf (const char *__format, ...)
__asm__("__mingw_printf");

__attribute__((__format__(__gnu_printf__,2,3))) __attribute__ ((__nonnull__ (2)))
int sprintf (char *__stream, const char *__format, ...)
__asm__("__mingw_sprintf");
# 374 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
__attribute__((__format__(__gnu_printf__,2,0))) __attribute__ ((__nonnull__ (2)))
int vfprintf (FILE *__stream, const char *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vfprintf");

__attribute__((__format__(__gnu_printf__,1,0))) __attribute__ ((__nonnull__ (1)))
int vprintf (const char *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vprintf");

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__(__gnu_printf__,2,0))) __attribute__ ((__nonnull__ (2)))
int vsprintf (char *__stream, const char *__format, __builtin_va_list __local_argv)
{
# 394 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  return __mingw_vsprintf( __stream, __format, __local_argv );
}


__attribute__((__format__(__gnu_printf__,3,4))) __attribute__ ((__nonnull__ (3)))
int snprintf (char *__stream, size_t __n, const char *__format, ...)
__asm__("__mingw_snprintf");
# 414 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__(__gnu_printf__,3,0))) __attribute__ ((__nonnull__ (3)))
int vsnprintf (char *__stream, size_t __n, const char *__format, __builtin_va_list __local_argv)
{



  return __mingw_vsnprintf( __stream, __n, __format, __local_argv );
}
# 535 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _filbuf(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flsbuf(int _Ch,FILE *_File);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fsopen(const char *_Filename,const char *_Mode,int _ShFlag);

  void __attribute__((__cdecl__)) clearerr(FILE *_File);
  int __attribute__((__cdecl__)) fclose(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fcloseall(void);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fdopen(int _FileHandle,const char *_Mode);

  int __attribute__((__cdecl__)) feof(FILE *_File);
  int __attribute__((__cdecl__)) ferror(FILE *_File);
  int __attribute__((__cdecl__)) fflush(FILE *_File);
  int __attribute__((__cdecl__)) fgetc(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fgetchar(void);
  int __attribute__((__cdecl__)) fgetpos(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  int __attribute__((__cdecl__)) fgetpos64(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  char *__attribute__((__cdecl__)) fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fileno(FILE *_File);







  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _tempnam(const char *_DirName,const char *_FilePrefix);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flushall(void);
  FILE *__attribute__((__cdecl__)) fopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode) ;
  FILE *fopen64(const char * __restrict__ filename,const char * __restrict__ mode);
  int __attribute__((__cdecl__)) fputc(int _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fputchar(int _Ch);
  int __attribute__((__cdecl__)) fputs(const char * __restrict__ _Str,FILE * __restrict__ _File);
  size_t __attribute__((__cdecl__)) fread(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  FILE *__attribute__((__cdecl__)) freopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode,FILE * __restrict__ _File) ;
  int __attribute__((__cdecl__)) fsetpos(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fsetpos64(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fseek(FILE *_File,long _Offset,int _Origin);
  long __attribute__((__cdecl__)) ftell(FILE *_File);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64(FILE *_File,long long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64(FILE *_File);
# 601 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  int fseeko64(FILE* stream, _off64_t offset, int whence);
  int fseeko(FILE* stream, _off_t offset, int whence);

  _off_t ftello(FILE * stream);
  _off64_t ftello64(FILE * stream);
# 622 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  size_t __attribute__((__cdecl__)) fwrite(const void * __restrict__ _Str,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) getc(FILE *_File);
  int __attribute__((__cdecl__)) getchar(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _getmaxstdio(void);
  char *__attribute__((__cdecl__)) gets(char *_Buffer)
    __attribute__((__warning__("Using gets() is always unsafe - use fgets() instead")));
  int __attribute__((__cdecl__)) _getw(FILE *_File);


  void __attribute__((__cdecl__)) perror(const char *_ErrMsg);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _pclose(FILE *_File);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _popen(const char *_Command,const char *_Mode);





  int __attribute__((__cdecl__)) putc(int _Ch,FILE *_File);
  int __attribute__((__cdecl__)) putchar(int _Ch);
  int __attribute__((__cdecl__)) puts(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putw(int _Word,FILE *_File);


  int __attribute__((__cdecl__)) remove(const char *_Filename);
  int __attribute__((__cdecl__)) rename(const char *_OldFilename,const char *_NewFilename);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _unlink(const char *_Filename);

  int __attribute__((__cdecl__)) unlink(const char *_Filename) ;


  void __attribute__((__cdecl__)) rewind(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _rmtmp(void);
  void __attribute__((__cdecl__)) setbuf(FILE * __restrict__ _File,char * __restrict__ _Buffer) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _setmaxstdio(int _Max);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_output_format(unsigned int _Format);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _get_output_format(void);
  int __attribute__((__cdecl__)) setvbuf(FILE * __restrict__ _File,char * __restrict__ _Buf,int _Mode,size_t _Size);







  __attribute__ ((__pure__))
  __attribute__((__format__(__ms_printf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf(const char * __restrict__ _Format,...);
  __attribute__((__format__(__ms_scanf__, 3,4))) __attribute__ ((__nonnull__ (3)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf(const char * __restrict__ _Src,size_t _MaxCount,const char * __restrict__ _Format,...) ;

  __attribute__ ((__pure__))
  __attribute__((__format__(__ms_printf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf(const char * __restrict__ _Format,va_list _ArgList);
  FILE *__attribute__((__cdecl__)) tmpfile(void) ;
  char *__attribute__((__cdecl__)) tmpnam(char *_Buffer);
  int __attribute__((__cdecl__)) ungetc(int _Ch,FILE *_File);







  __attribute__((__format__(__ms_printf__, 3,4))) __attribute__ ((__nonnull__ (3)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,...) ;
  __attribute__((__format__(__ms_printf__, 3,0))) __attribute__ ((__nonnull__ (3)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,va_list _Args) ;
# 905 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_printf_count_output(int _Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _get_printf_count_output(void);




                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vswscanf (const wchar_t * __restrict__ _Str,const wchar_t * __restrict__ Format,va_list argp);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wscanf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwscanf(const wchar_t * __restrict__ Format, va_list argp);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwscanf (FILE * __restrict__ fp, const wchar_t * __restrict__ Format,va_list argp);

                                                      __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                      __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wprintf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snwprintf (wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, ...);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnwprintf (wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_swprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vswprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ ,va_list);

                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...)
  ;
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vswscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,va_list)
  __asm__("vswscanf");
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wscanf(const wchar_t * __restrict__ _Format,...)
  ;
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vwscanf(const wchar_t * __restrict__ _Format, va_list)
  __asm__("vwscanf");
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...)
  ;
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list)
  __asm__("vfwscanf");

                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);


                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wprintf(const wchar_t * __restrict__ _Format,...)
  ;
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList)
  ;
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList)
  ;
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_swprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...)
  ;
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vswprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ ,va_list)
  ;
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_snwprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...)
  ;
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vsnwprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list)
  ;
# 998 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
                                                     __attribute__ ((__nonnull__ (2)))
int swscanf(const wchar_t *__source, const wchar_t *__format, ...)
__asm__("__mingw_swscanf");

                                                     __attribute__ ((__nonnull__ (1)))
int wscanf(const wchar_t *__format, ...)
__asm__("__mingw_wscanf");

                                                     __attribute__ ((__nonnull__ (2)))
int fwscanf(FILE *__stream, const wchar_t *__format, ...)
__asm__("__mingw_fwscanf");


                                                     __attribute__ ((__nonnull__ (2)))
int vswscanf (const wchar_t * __restrict__ __source, const wchar_t * __restrict__ __format, __builtin_va_list __local_argv)
__asm__("__mingw_vswscanf");

                                                     __attribute__ ((__nonnull__ (1)))
int vwscanf(const wchar_t *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vwscanf");

                                                     __attribute__ ((__nonnull__ (2)))
int vfwscanf (FILE *__stream, const wchar_t *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vfwscanf");




                                                      __attribute__ ((__nonnull__ (2)))
int fwprintf (FILE *__stream, const wchar_t *__format, ...)
__asm__("__mingw_fwprintf");

                                                      __attribute__ ((__nonnull__ (1)))
int wprintf (const wchar_t *__format, ...)
__asm__("__mingw_wprintf");

                                                      __attribute__ ((__nonnull__ (2)))
int vfwprintf (FILE *__stream, const wchar_t *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vfwprintf");

                                                      __attribute__ ((__nonnull__ (1)))
int vwprintf (const wchar_t *__format, __builtin_va_list __local_argv)
__asm__("__mingw_vwprintf");

                                                      __attribute__ ((__nonnull__ (3)))
int swprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, ...)
__asm__("__mingw_swprintf");
# 1058 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int vswprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, __builtin_va_list __local_argv)
{



  return __mingw_vswprintf( __stream, __n, __format, __local_argv );
}



                                                      __attribute__ ((__nonnull__ (3)))
int snwprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, ...)
__asm__("__mingw_snwprintf");
# 1086 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int vsnwprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, __builtin_va_list __local_argv)
{



  return __mingw_vsnwprintf( __stream, __n, __format, __local_argv );
}
# 1158 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfsopen(const wchar_t *_Filename,const wchar_t *_Mode,int _ShFlag);


  wint_t __attribute__((__cdecl__)) fgetwc(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwchar(void);
  wint_t __attribute__((__cdecl__)) fputwc(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) getwc(FILE *_File);
  wint_t __attribute__((__cdecl__)) getwchar(void);
  wint_t __attribute__((__cdecl__)) putwc(wchar_t _Ch,FILE *_File);
  wint_t __attribute__((__cdecl__)) putwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) ungetwc(wint_t _Ch,FILE *_File);
  wchar_t *__attribute__((__cdecl__)) fgetws(wchar_t * __restrict__ _Dst,int _SizeInWords,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) fputws(const wchar_t * __restrict__ _Str,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putws(const wchar_t *_Str);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf(const wchar_t * __restrict__ _Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,va_list _Args) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,va_list _Args);


# 1 "C:/mingw64/x86_64-w64-mingw32/include/swprintf.inl" 1 3
# 1188 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 2 3
# 1201 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtempnam(const wchar_t *_Directory,const wchar_t *_FilePrefix);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf(const wchar_t * __restrict__ _Src,size_t _MaxCount,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfdopen(int _FileHandle ,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfopen(const wchar_t * __restrict__ _Filename,const wchar_t *__restrict__ _Mode) ;
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfreopen(const wchar_t * __restrict__ _Filename,const wchar_t * __restrict__ _Mode,FILE * __restrict__ _OldFile) ;



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wperror(const wchar_t *_ErrMsg);

  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wpopen(const wchar_t *_Command,const wchar_t *_Mode);




  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wremove(const wchar_t *_Filename);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtmpnam(wchar_t *_Buffer);
# 1264 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _lock_file(FILE *_File);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _unlock_file(FILE *_File);
# 1286 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  char *__attribute__((__cdecl__)) tempnam(const char *_Directory,const char *_FilePrefix) ;



  int __attribute__((__cdecl__)) fcloseall(void) ;
  FILE *__attribute__((__cdecl__)) fdopen(int _FileHandle,const char *_Format) ;
  int __attribute__((__cdecl__)) fgetchar(void) ;
  int __attribute__((__cdecl__)) fileno(FILE *_File) ;
  int __attribute__((__cdecl__)) flushall(void) ;
  int __attribute__((__cdecl__)) fputchar(int _Ch) ;
  int __attribute__((__cdecl__)) getw(FILE *_File) ;
  int __attribute__((__cdecl__)) putw(int _Ch,FILE *_File) ;
  int __attribute__((__cdecl__)) rmtmp(void) ;
# 1315 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
int __attribute__((__cdecl__)) __mingw_str_wide_utf8 (const wchar_t * const wptr, char **mbptr, size_t * buflen);
# 1329 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
int __attribute__((__cdecl__)) __mingw_str_utf8_wide (const char *const mbptr, wchar_t ** wptr, size_t * buflen);
# 1338 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
void __attribute__((__cdecl__)) __mingw_str_free(void *ptr);






  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnl(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnle(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlp(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlpe(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnv(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnve(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvp(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvpe(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
# 1369 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 3
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnv(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnve(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvp(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvpe(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);







       
       
       
       

#pragma pack(pop)

# 1 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 1 3
# 9 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 2 3
# 29 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) clearerr_s(FILE *_File);

  size_t __attribute__((__cdecl__)) fread_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
# 515 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 3
  int __attribute__((__cdecl__)) fprintf_s(FILE *_File,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fscanf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fscanf_s(FILE *_File, const char *_Format, ...);
  int __attribute__((__cdecl__)) printf_s(const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scanf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scanf_s_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) scanf_s(const char *_Format, ...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fscanf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sscanf_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sscanf_s_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) sscanf_s(const char *_Src,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_s(const char *_Src,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_s_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  int __attribute__((__cdecl__)) vfprintf_s(FILE *_File,const char *_Format,va_list _ArgList);
  int __attribute__((__cdecl__)) vprintf_s(const char *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__((dllimport)) int __attribute__((__cdecl__)) vsprintf_s(char *_DstBuf,size_t _Size,const char *_Format,va_list _ArgList);

  __attribute__((dllimport)) int __attribute__((__cdecl__)) sprintf_s(char *_DstBuf,size_t _DstSize,const char *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_p(FILE *_File,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_p(const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_p(FILE *_File,const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_p(const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_p(const char *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vscprintf_p(const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_p_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_l(char *_DstBuf,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_l(char *_DstBuf,const char *_Format,_locale_t,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_p_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_s_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_s_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *,_locale_t _Locale,va_list _ArgList);


 
 
 
 
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) fopen_s(FILE **_File,const char *_Filename,const char *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) freopen_s(FILE** _File, const char *_Filename, const char *_Mode, FILE *_Stream);

  __attribute__ ((__dllimport__)) char* __attribute__((__cdecl__)) gets_s(char*,rsize_t);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpfile_s(FILE **_File);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpnam_s(char*,rsize_t);
 




  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws_s(wchar_t *_Str,size_t _SizeInWords);
 
# 830 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdio_s.h" 3
  int __attribute__((__cdecl__)) fwprintf_s(FILE *_File,const wchar_t *_Format,...);
  int __attribute__((__cdecl__)) wprintf_s(const wchar_t *_Format,...);
  int __attribute__((__cdecl__)) vfwprintf_s(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  int __attribute__((__cdecl__)) vwprintf_s(const wchar_t *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) vswprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) swprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,...);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_s_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwscanf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fwscanf_s(FILE *_File, const wchar_t *_Format, ...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swscanf_s_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) swscanf_s(const wchar_t *_Src,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_s(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_s_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wscanf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) wscanf_s(const wchar_t *_Format, ...);


 
 
 
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfreopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode,FILE *_OldFile);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wtmpnam_s(wchar_t *_DstBuf,size_t _SizeInWords);
 


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_p(FILE *_File,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_p(const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_p(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_p(const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vswprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_p(const wchar_t *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vscwprintf_p(const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __swprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __vswprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,va_list _Args);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwscanf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swscanf_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wscanf_l(const wchar_t *_Format,_locale_t _Locale,...);
# 1388 "C:/mingw64/x86_64-w64-mingw32/include/stdio.h" 2 3
# 9 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
       
# 11 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3


# 1 "C:/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 1 3
# 14 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 2 3

struct _exception;

#pragma pack(push,_CRT_PACKING)
# 117 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  typedef union __mingw_dbl_type_t {
    double x;
    unsigned long long val;
    __extension__ struct {
      unsigned int low, high;
    } lh;
  } __mingw_dbl_type_t;

  typedef union __mingw_flt_type_t {
    float x;
    unsigned int val;
  } __mingw_flt_type_t;

  typedef union __mingw_ldbl_type_t
  {
    long double x;
    __extension__ struct {
      unsigned int low, high;
      int sign_exponent : 16;
      int res1 : 16;
      int res0 : 32;
    } lh;
  } __mingw_ldbl_type_t;




  extern double * __imp__HUGE;
# 156 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  struct _exception {
    int type;
    const char *name;
    double arg1;
    double arg2;
    double retval;
  };

  void __mingw_raise_matherr (int typ, const char *name, double a1, double a2,
         double rslt);
  void __mingw_setusermatherr (int (__attribute__((__cdecl__)) *)(struct _exception *));
  __attribute__ ((__dllimport__)) void __setusermatherr(int (__attribute__((__cdecl__)) *)(struct _exception *));



  double __attribute__((__cdecl__)) sin(double _X);
  double __attribute__((__cdecl__)) cos(double _X);
  double __attribute__((__cdecl__)) tan(double _X);
  double __attribute__((__cdecl__)) sinh(double _X);
  double __attribute__((__cdecl__)) cosh(double _X);
  double __attribute__((__cdecl__)) tanh(double _X);
  double __attribute__((__cdecl__)) asin(double _X);
  double __attribute__((__cdecl__)) acos(double _X);
  double __attribute__((__cdecl__)) atan(double _X);
  double __attribute__((__cdecl__)) atan2(double _Y,double _X);
  double __attribute__((__cdecl__)) exp(double _X);
  double __attribute__((__cdecl__)) log(double _X);
  double __attribute__((__cdecl__)) log10(double _X);
  double __attribute__((__cdecl__)) pow(double _X,double _Y);
  double __attribute__((__cdecl__)) sqrt(double _X);
  double __attribute__((__cdecl__)) ceil(double _X);
  double __attribute__((__cdecl__)) floor(double _X);


  extern float __attribute__((__cdecl__)) fabsf (float x);
  extern long double __attribute__((__cdecl__)) fabsl (long double);
  extern double __attribute__((__cdecl__)) fabs (double _X);
# 231 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  double __attribute__((__cdecl__)) ldexp(double _X,int _Y);
  double __attribute__((__cdecl__)) frexp(double _X,int *_Y);
  double __attribute__((__cdecl__)) modf(double _X,double *_Y);
  double __attribute__((__cdecl__)) fmod(double _X,double _Y);

  void __attribute__((__cdecl__)) sincos (double __x, double *p_sin, double *p_cos);
  void __attribute__((__cdecl__)) sincosl (long double __x, long double *p_sin, long double *p_cos);
  void __attribute__((__cdecl__)) sincosf (float __x, float *p_sin, float *p_cos);



  int __attribute__((__cdecl__)) abs(int _X);
  long __attribute__((__cdecl__)) labs(long _X);



  double __attribute__((__cdecl__)) atof(const char *_String);
  double __attribute__((__cdecl__)) _atof_l(const char *_String,_locale_t _Locale);







  struct _complex {
    double x;
    double y;
  };


  double __attribute__((__cdecl__)) _cabs(struct _complex _ComplexA);
  double __attribute__((__cdecl__)) _hypot(double _X,double _Y);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _j0(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _j1(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _jn(int _X,double _Y);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _y0(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _y1(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _yn(int _X,double _Y);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _matherr (struct _exception *);
# 283 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _chgsign (double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _copysign (double _Number,double _Sign);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _logb (double);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _nextafter (double, double);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _scalb (double, long);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _finite (double);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fpclass (double);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isnan (double);






__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) j0 (double) ;
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) j1 (double) ;
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) jn (int, double) ;
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) y0 (double) ;
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) y1 (double) ;
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) yn (int, double) ;



__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) chgsign (double);
# 315 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) finite (double);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fpclass (double);
# 359 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
typedef float float_t;
typedef double double_t;
# 394 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern int __attribute__((__cdecl__)) __fpclassifyl (long double);
  extern int __attribute__((__cdecl__)) __fpclassifyf (float);
  extern int __attribute__((__cdecl__)) __fpclassify (double);
# 507 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern int __attribute__((__cdecl__)) __isnan (double);
  extern int __attribute__((__cdecl__)) __isnanf (float);
  extern int __attribute__((__cdecl__)) __isnanl (long double);
# 594 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern int __attribute__((__cdecl__)) __signbit (double);
  extern int __attribute__((__cdecl__)) __signbitf (float);
  extern int __attribute__((__cdecl__)) __signbitl (long double);
# 651 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern float __attribute__((__cdecl__)) sinf(float _X);
  extern long double __attribute__((__cdecl__)) sinl(long double);

  extern float __attribute__((__cdecl__)) cosf(float _X);
  extern long double __attribute__((__cdecl__)) cosl(long double);

  extern float __attribute__((__cdecl__)) tanf(float _X);
  extern long double __attribute__((__cdecl__)) tanl(long double);
  extern float __attribute__((__cdecl__)) asinf(float _X);
  extern long double __attribute__((__cdecl__)) asinl(long double);

  extern float __attribute__((__cdecl__)) acosf (float);
  extern long double __attribute__((__cdecl__)) acosl (long double);

  extern float __attribute__((__cdecl__)) atanf (float);
  extern long double __attribute__((__cdecl__)) atanl (long double);

  extern float __attribute__((__cdecl__)) atan2f (float, float);
  extern long double __attribute__((__cdecl__)) atan2l (long double, long double);


  extern float __attribute__((__cdecl__)) sinhf(float _X);



  extern long double __attribute__((__cdecl__)) sinhl(long double);

  extern float __attribute__((__cdecl__)) coshf(float _X);



  extern long double __attribute__((__cdecl__)) coshl(long double);

  extern float __attribute__((__cdecl__)) tanhf(float _X);



  extern long double __attribute__((__cdecl__)) tanhl(long double);



  extern double __attribute__((__cdecl__)) acosh (double);
  extern float __attribute__((__cdecl__)) acoshf (float);
  extern long double __attribute__((__cdecl__)) acoshl (long double);


  extern double __attribute__((__cdecl__)) asinh (double);
  extern float __attribute__((__cdecl__)) asinhf (float);
  extern long double __attribute__((__cdecl__)) asinhl (long double);


  extern double __attribute__((__cdecl__)) atanh (double);
  extern float __attribute__((__cdecl__)) atanhf (float);
  extern long double __attribute__((__cdecl__)) atanhl (long double);



  extern float __attribute__((__cdecl__)) expf(float _X);



  extern long double __attribute__((__cdecl__)) expl(long double);


  extern double __attribute__((__cdecl__)) exp2(double);
  extern float __attribute__((__cdecl__)) exp2f(float);
  extern long double __attribute__((__cdecl__)) exp2l(long double);



  extern double __attribute__((__cdecl__)) expm1(double);
  extern float __attribute__((__cdecl__)) expm1f(float);
  extern long double __attribute__((__cdecl__)) expm1l(long double);


  extern float frexpf(float _X,int *_Y);



  extern long double __attribute__((__cdecl__)) frexpl(long double,int *);




  extern int __attribute__((__cdecl__)) ilogb (double);
  extern int __attribute__((__cdecl__)) ilogbf (float);
  extern int __attribute__((__cdecl__)) ilogbl (long double);


  extern float __attribute__((__cdecl__)) ldexpf(float _X,int _Y);



  extern long double __attribute__((__cdecl__)) ldexpl (long double, int);


  extern float __attribute__((__cdecl__)) logf (float);
  extern long double __attribute__((__cdecl__)) logl(long double);


  extern float __attribute__((__cdecl__)) log10f (float);
  extern long double __attribute__((__cdecl__)) log10l(long double);


  extern double __attribute__((__cdecl__)) log1p(double);
  extern float __attribute__((__cdecl__)) log1pf(float);
  extern long double __attribute__((__cdecl__)) log1pl(long double);


  extern double __attribute__((__cdecl__)) log2 (double);
  extern float __attribute__((__cdecl__)) log2f (float);
  extern long double __attribute__((__cdecl__)) log2l (long double);


  extern double __attribute__((__cdecl__)) logb (double);
  extern float __attribute__((__cdecl__)) logbf (float);
  extern long double __attribute__((__cdecl__)) logbl (long double);


  extern float __attribute__((__cdecl__)) modff (float, float*);
  extern long double __attribute__((__cdecl__)) modfl (long double, long double*);


  extern double __attribute__((__cdecl__)) scalbn (double, int);
  extern float __attribute__((__cdecl__)) scalbnf (float, int);
  extern long double __attribute__((__cdecl__)) scalbnl (long double, int);

  extern double __attribute__((__cdecl__)) scalbln (double, long);
  extern float __attribute__((__cdecl__)) scalblnf (float, long);
  extern long double __attribute__((__cdecl__)) scalblnl (long double, long);



  extern double __attribute__((__cdecl__)) cbrt (double);
  extern float __attribute__((__cdecl__)) cbrtf (float);
  extern long double __attribute__((__cdecl__)) cbrtl (long double);


  extern double __attribute__((__cdecl__)) hypot (double, double) ;
  extern float __attribute__((__cdecl__)) hypotf (float x, float y);



  extern long double __attribute__((__cdecl__)) hypotl (long double, long double);


  extern float __attribute__((__cdecl__)) powf(float _X,float _Y);



  extern long double __attribute__((__cdecl__)) powl (long double, long double);


  extern float __attribute__((__cdecl__)) sqrtf (float);
  extern long double sqrtl(long double);


  extern double __attribute__((__cdecl__)) erf (double);
  extern float __attribute__((__cdecl__)) erff (float);
  extern long double __attribute__((__cdecl__)) erfl (long double);


  extern double __attribute__((__cdecl__)) erfc (double);
  extern float __attribute__((__cdecl__)) erfcf (float);
  extern long double __attribute__((__cdecl__)) erfcl (long double);


  extern double __attribute__((__cdecl__)) lgamma (double);
  extern float __attribute__((__cdecl__)) lgammaf (float);
  extern long double __attribute__((__cdecl__)) lgammal (long double);

  extern int signgam;


  extern double __attribute__((__cdecl__)) tgamma (double);
  extern float __attribute__((__cdecl__)) tgammaf (float);
  extern long double __attribute__((__cdecl__)) tgammal (long double);


  extern float __attribute__((__cdecl__)) ceilf (float);
  extern long double __attribute__((__cdecl__)) ceill (long double);


  extern float __attribute__((__cdecl__)) floorf (float);
  extern long double __attribute__((__cdecl__)) floorl (long double);


  extern double __attribute__((__cdecl__)) nearbyint ( double);
  extern float __attribute__((__cdecl__)) nearbyintf (float);
  extern long double __attribute__((__cdecl__)) nearbyintl (long double);



extern double __attribute__((__cdecl__)) rint (double);
extern float __attribute__((__cdecl__)) rintf (float);
extern long double __attribute__((__cdecl__)) rintl (long double);


extern long __attribute__((__cdecl__)) lrint (double);
extern long __attribute__((__cdecl__)) lrintf (float);
extern long __attribute__((__cdecl__)) lrintl (long double);

__extension__ long long __attribute__((__cdecl__)) llrint (double);
__extension__ long long __attribute__((__cdecl__)) llrintf (float);
__extension__ long long __attribute__((__cdecl__)) llrintl (long double);



  extern double __attribute__((__cdecl__)) round (double);
  extern float __attribute__((__cdecl__)) roundf (float);
  extern long double __attribute__((__cdecl__)) roundl (long double);


  extern long __attribute__((__cdecl__)) lround (double);
  extern long __attribute__((__cdecl__)) lroundf (float);
  extern long __attribute__((__cdecl__)) lroundl (long double);
  __extension__ long long __attribute__((__cdecl__)) llround (double);
  __extension__ long long __attribute__((__cdecl__)) llroundf (float);
  __extension__ long long __attribute__((__cdecl__)) llroundl (long double);



  extern double __attribute__((__cdecl__)) trunc (double);
  extern float __attribute__((__cdecl__)) truncf (float);
  extern long double __attribute__((__cdecl__)) truncl (long double);


  extern float __attribute__((__cdecl__)) fmodf (float, float);
  extern long double __attribute__((__cdecl__)) fmodl (long double, long double);


  extern double __attribute__((__cdecl__)) remainder (double, double);
  extern float __attribute__((__cdecl__)) remainderf (float, float);
  extern long double __attribute__((__cdecl__)) remainderl (long double, long double);


  extern double __attribute__((__cdecl__)) remquo(double, double, int *);
  extern float __attribute__((__cdecl__)) remquof(float, float, int *);
  extern long double __attribute__((__cdecl__)) remquol(long double, long double, int *);


  extern double __attribute__((__cdecl__)) copysign (double, double);
  extern float __attribute__((__cdecl__)) copysignf (float, float);
  extern long double __attribute__((__cdecl__)) copysignl (long double, long double);
# 916 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern double __attribute__((__cdecl__)) nan(const char *tagp);
  extern float __attribute__((__cdecl__)) nanf(const char *tagp);
  extern long double __attribute__((__cdecl__)) nanl(const char *tagp);
# 927 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
  extern double __attribute__((__cdecl__)) nextafter (double, double);
  extern float __attribute__((__cdecl__)) nextafterf (float, float);
  extern long double __attribute__((__cdecl__)) nextafterl (long double, long double);


  extern double __attribute__((__cdecl__)) nexttoward (double, long double);
  extern float __attribute__((__cdecl__)) nexttowardf (float, long double);
  extern long double __attribute__((__cdecl__)) nexttowardl (long double, long double);



  extern double __attribute__((__cdecl__)) fdim (double x, double y);
  extern float __attribute__((__cdecl__)) fdimf (float x, float y);
  extern long double __attribute__((__cdecl__)) fdiml (long double x, long double y);







  extern double __attribute__((__cdecl__)) fmax (double, double);
  extern float __attribute__((__cdecl__)) fmaxf (float, float);
  extern long double __attribute__((__cdecl__)) fmaxl (long double, long double);


  extern double __attribute__((__cdecl__)) fmin (double, double);
  extern float __attribute__((__cdecl__)) fminf (float, float);
  extern long double __attribute__((__cdecl__)) fminl (long double, long double);



  extern double __attribute__((__cdecl__)) fma (double, double, double);
  extern float __attribute__((__cdecl__)) fmaf (float, float, float);
  extern long double __attribute__((__cdecl__)) fmal (long double, long double, long double);
# 1010 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _copysignf (float _Number,float _Sign);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _chgsignf (float _X);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _logbf(float _X);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _nextafterf(float _X,float _Y);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _finitef(float _X);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isnanf(float _X);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fpclassf(float _X);



   extern long double __attribute__((__cdecl__)) _chgsignl (long double);
# 1410 "C:/mingw64/x86_64-w64-mingw32/include/math.h" 3
#pragma pack(pop)
# 10 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/corecrt_wstdlib.h" 1 3
# 19 "C:/mingw64/x86_64-w64-mingw32/include/corecrt_wstdlib.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wdupenv_s(wchar_t **_Buffer,size_t *_BufferSizeInWords,const wchar_t *_VarName);




  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itow_s (int _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltow_s (long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultow_s (unsigned long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wgetenv_s(size_t *_ReturnSize,wchar_t *_DstBuf,size_t _DstSizeInWords,const wchar_t *_VarName);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64tow_s(long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64tow_s(unsigned long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wmakepath_s(wchar_t *_PathResult,size_t _SizeInWords,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wputenv_s(const wchar_t *_Name,const wchar_t *_Value);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsearchenv_s(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath,size_t _SizeInWords);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsplitpath_s(const wchar_t *_FullPath,wchar_t *_Drive,size_t _DriveSizeInWords,wchar_t *_Dir,size_t _DirSizeInWords,wchar_t *_Filename,size_t _FilenameSizeInWords,wchar_t *_Ext,size_t _ExtSizeInWords);
 
# 11 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 2 3
# 1 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 1 3 4
# 34 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 3 4
# 1 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/syslimits.h" 1 3 4






 
# 7 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/syslimits.h" 3 4
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 1 3 4
# 210 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 3 4
# 1 "C:/mingw64/x86_64-w64-mingw32/include/limits.h" 1 3 4
# 211 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 2 3 4
# 10 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/syslimits.h" 2 3 4
#pragma GCC diagnostic pop
# 35 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/limits.h" 2 3 4
# 12 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 2 3
# 26 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
#pragma pack(push,_CRT_PACKING)
# 50 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  typedef int (__attribute__((__cdecl__)) *_onexit_t)(void);
# 60 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  typedef struct _div_t {
    int quot;
    int rem;
  } div_t;

  typedef struct _ldiv_t {
    long quot;
    long rem;
  } ldiv_t;





#pragma pack(4)
  typedef struct {
    unsigned char ld[10];
  } _LDOUBLE;
#pragma pack()



  typedef struct {
    double x;
  } _CRT_DOUBLE;

  typedef struct {
    float f;
  } _CRT_FLOAT;

       


  typedef struct {
    long double x;
  } _LONGDOUBLE;

       

#pragma pack(4)
  typedef struct {
    unsigned char ld12[12];
  } _LDBL12;
#pragma pack()
# 113 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) ___mb_cur_max_func(void);
# 135 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  typedef void (__attribute__((__cdecl__)) *_purecall_handler)(void);

  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _set_purecall_handler(_purecall_handler _Handler);
  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _get_purecall_handler(void);

  typedef void (__attribute__((__cdecl__)) *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _set_invalid_parameter_handler(_invalid_parameter_handler _Handler);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _get_invalid_parameter_handler(void);



  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);

  __attribute__ ((__dllimport__)) unsigned long *__attribute__((__cdecl__)) __doserrno(void);

  errno_t __attribute__((__cdecl__)) _set_doserrno(unsigned long _Value);
  errno_t __attribute__((__cdecl__)) _get_doserrno(unsigned long *_Value);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __sys_errlist(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __sys_nerr(void);



  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p___argv(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p__fmode(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p___argc(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p___wargv(void);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __p__pgmptr(void);
  __attribute__ ((__dllimport__)) wchar_t **__attribute__((__cdecl__)) __p__wpgmptr(void);

  errno_t __attribute__((__cdecl__)) _get_pgmptr(char **_Value);
  errno_t __attribute__((__cdecl__)) _get_wpgmptr(wchar_t **_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_fmode(int _Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_fmode(int *_PMode);
# 221 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p__environ(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p__wenviron(void);
# 234 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osplatform(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winmajor(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winminor(void);
# 256 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  errno_t __attribute__((__cdecl__)) _get_osplatform(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_osver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winmajor(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winminor(unsigned int *_Value);
# 274 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit(int _Code) __attribute__ ((__noreturn__));
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit(int _Code) __attribute__ ((__noreturn__));






  void __attribute__((__cdecl__)) _Exit(int) __attribute__ ((__noreturn__));






       

  void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) abort(void);
       



  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_abort_behavior(unsigned int _Flags,unsigned int _Mask);







  __extension__ long long __attribute__((__cdecl__)) _abs64(long long);

  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) long long __attribute__((__cdecl__)) _abs64(long long x) {
    return __builtin_llabs(x);
  }


  int __attribute__((__cdecl__)) atexit(void (__attribute__((__cdecl__)) *)(void));
# 320 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  int __attribute__((__cdecl__)) atoi(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoi_l(const char *_Str,_locale_t _Locale);
  long __attribute__((__cdecl__)) atol(const char *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _atol_l(const char *_Str,_locale_t _Locale);


  void *__attribute__((__cdecl__)) bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));
  void __attribute__((__cdecl__)) qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));

  unsigned short __attribute__((__cdecl__)) _byteswap_ushort(unsigned short _Short);
  unsigned long __attribute__((__cdecl__)) _byteswap_ulong (unsigned long _Long);
  __extension__ unsigned long long __attribute__((__cdecl__)) _byteswap_uint64(unsigned long long _Int64);
  div_t __attribute__((__cdecl__)) div(int _Numerator,int _Denominator);
  char *__attribute__((__cdecl__)) getenv(const char *_VarName) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _itoa(int _Value,char *_Dest,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _i64toa(long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ui64toa(unsigned long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64(const char *_String);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64_l(const char *_String,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  ldiv_t __attribute__((__cdecl__)) ldiv(long _Numerator,long _Denominator);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ltoa(long _Value,char *_Dest,int _Radix) ;
  int __attribute__((__cdecl__)) mblen(const char *_Ch,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mblen_l(const char *_Ch,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen(const char *_Str);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen_l(const char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen(const char *_Str,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen_l(const char *_Str,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) mbtowc(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mbtowc_l(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale);
  size_t __attribute__((__cdecl__)) mbstowcs(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstowcs_l(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) mkstemp(char *template_name);
  int __attribute__((__cdecl__)) rand(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_error_mode(int _Mode);
  void __attribute__((__cdecl__)) srand(unsigned int _Seed);
# 369 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtod(const char * __restrict__ _Str,char ** __restrict__ _EndPtr)
{
  double __attribute__((__cdecl__)) __mingw_strtod (const char * __restrict__, char ** __restrict__);
  return __mingw_strtod( _Str, _EndPtr);
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtof(const char * __restrict__ _Str,char ** __restrict__ _EndPtr)
{
  float __attribute__((__cdecl__)) __mingw_strtof (const char * __restrict__, char ** __restrict__);
  return __mingw_strtof( _Str, _EndPtr);
}






  long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtold(const char * __restrict__ , char ** __restrict__ );


  extern double __attribute__((__cdecl__)) __attribute__ ((__nothrow__))
  __strtod (const char * __restrict__ , char ** __restrict__);







  float __attribute__((__cdecl__)) __mingw_strtof (const char * __restrict__, char ** __restrict__);
  double __attribute__((__cdecl__)) __mingw_strtod (const char * __restrict__, char ** __restrict__);
  long double __attribute__((__cdecl__)) __mingw_strtold(const char * __restrict__, char ** __restrict__);

  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _strtof_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _strtod_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) strtol(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _strtol_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) strtoul(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _strtoul_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);


  int __attribute__((__cdecl__)) system(const char *_Command);

  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ultoa(unsigned long _Value,char *_Dest,int _Radix) ;
  int __attribute__((__cdecl__)) wctomb(char *_MbCh,wchar_t _WCh) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wctomb_l(char *_MbCh,wchar_t _WCh,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) wcstombs(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcstombs_l(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale) ;
# 452 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  void *__attribute__((__cdecl__)) calloc(size_t _NumOfElements,size_t _SizeOfElements);
  void __attribute__((__cdecl__)) free(void *_Memory);
  void *__attribute__((__cdecl__)) malloc(size_t _Size);
  void *__attribute__((__cdecl__)) realloc(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _aligned_free(void *_Memory);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_malloc(size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_realloc(void *_Memory,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_realloc(void *_Memory,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _recalloc(void *_Memory,size_t _Count,size_t _Size);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _aligned_msize(void *_Memory,size_t _Alignment,size_t _Offset);
# 487 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _itow(int _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ltow(long _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ultow(unsigned long _Value,wchar_t *_Dest,int _Radix) ;

  double __attribute__((__cdecl__)) __mingw_wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) __mingw_wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);
  long double __attribute__((__cdecl__)) __mingw_wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);


  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
  double __attribute__((__cdecl__)) wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr){
    return __mingw_wcstod(_Str,_EndPtr);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
  float __attribute__((__cdecl__)) wcstof(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr){
    return __mingw_wcstof(_Str,_EndPtr);
  }






  long double __attribute__((__cdecl__)) wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wcstod_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _wcstof_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) wcstol(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wcstol_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) wcstoul(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _wcstoul_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wgetenv(const wchar_t *_VarName) ;


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wsystem(const wchar_t *_Command);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol_l(const wchar_t *_Str,_locale_t _Locale);

  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _i64tow(long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ui64tow(unsigned long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64(const wchar_t *_Str);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64_l(const wchar_t *_Str,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64_l(const wchar_t *_Str ,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putenv(const char *_EnvString);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wputenv(const wchar_t *_EnvString);
# 550 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fullpath(char *_FullPath,const char *_Path,size_t _SizeInBytes);




  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl(_CRT_DOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl(_LDOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt(_CRT_FLOAT *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl_l(_CRT_DOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl_l(_LDOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt_l(_CRT_FLOAT *_Result,char *_Str,_locale_t _Locale);
# 579 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
unsigned long __attribute__((__cdecl__)) _lrotl(unsigned long,int);
unsigned long __attribute__((__cdecl__)) _lrotr(unsigned long,int);





  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _makepath(char *_Path,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  _onexit_t __attribute__((__cdecl__)) _onexit(_onexit_t _Func);





       
       


  __extension__ unsigned long long __attribute__((__cdecl__)) _rotl64(unsigned long long _Val,int _Shift);
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long Value,int Shift);
       
       
       
       


  unsigned int __attribute__((__cdecl__)) _rotr(unsigned int _Val,int _Shift);
  unsigned int __attribute__((__cdecl__)) _rotl(unsigned int _Val,int _Shift);
       
       
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long _Val,int _Shift);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _searchenv(const char *_Filename,const char *_EnvVar,char *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _splitpath(const char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _swab(char *_Buf1,char *_Buf2,int _SizeInBytes);







  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wfullpath(wchar_t *_FullPath,const wchar_t *_Path,size_t _SizeInWords);



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wmakepath(wchar_t *_ResultPath,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);




  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsearchenv(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsplitpath(const wchar_t *_FullPath,wchar_t *_Drive,wchar_t *_Dir,wchar_t *_Filename,wchar_t *_Ext) ;


  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _beep(unsigned _Frequency,unsigned _Duration) __attribute__ ((__deprecated__));

  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _seterrormode(int _Mode) __attribute__ ((__deprecated__));
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _sleep(unsigned long _Duration) __attribute__ ((__deprecated__));
# 657 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
  char *__attribute__((__cdecl__)) ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  char *__attribute__((__cdecl__)) itoa(int _Val,char *_DstBuf,int _Radix) ;
  char *__attribute__((__cdecl__)) ltoa(long _Val,char *_DstBuf,int _Radix) ;
  int __attribute__((__cdecl__)) putenv(const char *_EnvString) ;



  void __attribute__((__cdecl__)) swab(char *_Buf1,char *_Buf2,int _SizeInBytes) ;


  char *__attribute__((__cdecl__)) ultoa(unsigned long _Val,char *_Dstbuf,int _Radix) ;
  _onexit_t __attribute__((__cdecl__)) onexit(_onexit_t _Func);





  typedef struct { __extension__ long long quot, rem; } lldiv_t;

  __extension__ lldiv_t __attribute__((__cdecl__)) lldiv(long long, long long);

  __extension__ long long __attribute__((__cdecl__)) llabs(long long);




  __extension__ long long __attribute__((__cdecl__)) strtoll(const char * __restrict__, char ** __restrict, int);
  __extension__ unsigned long long __attribute__((__cdecl__)) strtoull(const char * __restrict__, char ** __restrict__, int);


  __extension__ long long __attribute__((__cdecl__)) atoll (const char *);


  __extension__ long long __attribute__((__cdecl__)) wtoll (const wchar_t *);
  __extension__ char *__attribute__((__cdecl__)) lltoa (long long, char *, int);
  __extension__ char *__attribute__((__cdecl__)) ulltoa (unsigned long long , char *, int);
  __extension__ wchar_t *__attribute__((__cdecl__)) lltow (long long, wchar_t *, int);
  __extension__ wchar_t *__attribute__((__cdecl__)) ulltow (unsigned long long, wchar_t *, int);
# 714 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 3
#pragma pack(pop)

# 1 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdlib_s.h" 1 3
# 9 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdlib_s.h" 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 1 3
# 10 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdlib_s.h" 2 3
# 19 "C:/mingw64/x86_64-w64-mingw32/include/sec_api/stdlib_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _dupenv_s(char **_PBuffer,size_t *_PBufferSizeInBytes,const char *_VarName);




  __attribute__ ((__dllimport__)) void * __attribute__((__cdecl__)) bsearch_s(const void *_Key,const void *_Base,rsize_t _NumOfElements,rsize_t _SizeOfElements,int (__attribute__((__cdecl__)) * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) getenv_s(size_t *_ReturnSize,char *_DstBuf,rsize_t _DstSize,const char *_VarName);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itoa_s(int _Value,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64toa_s(long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64toa_s(unsigned long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltoa_s(long _Val,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) mbstowcs_s(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _mbstowcs_s_l(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount,_locale_t _Locale);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultoa_s(unsigned long _Val,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wctomb_s(int *_SizeConverted,char *_MbCh,rsize_t _SizeInBytes,wchar_t _WCh);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wctomb_s_l(int *_SizeConverted,char *_MbCh,size_t _SizeInBytes,wchar_t _WCh,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcstombs_s(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcstombs_s_l(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes,_locale_t _Locale);
 


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ecvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDights,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _fcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _gcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDigits);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _makepath_s(char *_PathResult,size_t _Size,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _putenv_s(const char *_Name,const char *_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _searchenv_s(const char *_Filename,const char *_EnvVar,char *_ResultPath,size_t _SizeInBytes);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _splitpath_s(const char *_FullPath,char *_Drive,size_t _DriveSize,char *_Dir,size_t _DirSize,char *_Filename,size_t _FilenameSize,char *_Ext,size_t _ExtSize);
 



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) qsort_s(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(void *,const void *,const void *),void *_Context);
# 717 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 2 3
# 1 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 1 3
# 11 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
#pragma pack(push,_CRT_PACKING)
# 52 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
  typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;



  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__amblksiz(void);
# 129 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
void * __mingw_aligned_malloc (size_t _Size, size_t _Alignment);
void __mingw_aligned_free (void *_Memory);
void * __mingw_aligned_offset_realloc (void *_Memory, size_t _Size, size_t _Alignment, size_t _Offset);
void * __mingw_aligned_offset_malloc (size_t, size_t, size_t);
void * __mingw_aligned_realloc (void *_Memory, size_t _Size, size_t _Offset);
size_t __mingw_aligned_msize (void *memblock, size_t alignment, size_t offset);



# 1 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/mm_malloc.h" 1 3 4
# 29 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/mm_malloc.h" 3 4
# 1 "C:/mingw64/x86_64-w64-mingw32/include/errno.h" 1 3 4
# 30 "C:/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/mm_malloc.h" 2 3 4


static __inline__ void *
_mm_malloc (size_t __size, size_t __align)
{
  void * __malloc_ptr;
  void * __aligned_ptr;


  if (__align & (__align - 1))
    {

      (*_errno()) = 22;

      return ((void *) 0);
    }

  if (__size == 0)
    return ((void *) 0);





    if (__align < 2 * sizeof (void *))
      __align = 2 * sizeof (void *);

  __malloc_ptr = malloc (__size + __align);
  if (!__malloc_ptr)
    return ((void *) 0);


  __aligned_ptr = (void *) (((size_t) __malloc_ptr + __align)
       & ~((size_t) (__align) - 1));


  ((void **) __aligned_ptr)[-1] = __malloc_ptr;

  return __aligned_ptr;
}

static __inline__ void
_mm_free (void *__aligned_ptr)
{
  if (__aligned_ptr)
    free (((void **) __aligned_ptr)[-1]);
}
# 139 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 2 3





  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _resetstkoflw (void);

  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _set_malloc_crt_max_wait(unsigned long _NewValue);







  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _expand(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _msize(void *_Memory);
# 167 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _get_sbh_threshold(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_sbh_threshold(size_t _NewValue);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_amblksiz(size_t _Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_amblksiz(size_t *_Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapadd(void *_Memory,size_t _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapchk(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapmin(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapset(unsigned int _Fill);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapwalk(_HEAPINFO *_EntryInfo);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _heapused(size_t *_Used,size_t *_Commit);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _get_heap_handle(void);
# 190 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + 16;
    }
    return _Ptr;
  }
# 218 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
  static __inline void __attribute__((__cdecl__)) _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - 16;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==0xDDDD) {
 free(_Memory);
      }





    }
  }
# 264 "C:/mingw64/x86_64-w64-mingw32/include/malloc.h" 3
#pragma pack(pop)
# 718 "C:/mingw64/x86_64-w64-mingw32/include/stdlib.h" 2 3
# 11 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2






# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\global.h" 1
# 60 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\global.h"
 
# 60 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\global.h"
      unsigned int ( *dim[3] )(int, int);


 unsigned int it[3], jt[3];
 unsigned int dG[3], dE[3];

 double *x_xi[3], *y_xi[3];
 double *x_eta[3], *y_eta[3];
 double *x_xi_cen[3], *y_xi_cen[3];
 double *x_eta_cen[3], *y_eta_cen[3];
 double *S[3];
 double *x[3], *y[3];
 double *cen_x[3], *cen_y[3];
 double *cx[3], *cy[3];

 double *rho[3];
 double *ux[3];
 double *uy[3];
 double *p[3];
 double *e[3];
 double *Q[3][4];
 double *tmpQ[3][4];
 double *E[3][4];
 double *F[3][4];
 double *Ecen[3][6];
 double *Fcen[3][6];
 double *Ev[3][4];
 double *Fv[3][4];


 double *vis_S[3][2];
 double *duxd[3][2], *duyd[3][2], *dcptd[3][2];


 double *Qch[3][6][2];
 double *Qchcv[3][4][2];
 double *TurbQchcv[3][2][2];


 double *tmpEE[3][4];
 double *dQ[3][4];
 double *rhsF[3][4];


 double *d_wall[3], *yp[3], *Mut[3], *k_turb[3], *omega[3], *ut_buff[3];
 double *TurbE[3][2], *TurbF[3][2];
 double *TurbEv[3][2], *TurbFv[3][2];
 double *TurbQ[3][2], *TurbtmpQ[3][2], *TurbdQ[3][2], *TurbtmpEE[3][2], *rhsTurbF[3][2];
 int *clx[3], *cly[3];


 double *NuSA[3];


 double *deruta_x[3], *deruta_y[3];
 double *RA_LE[3], *lkw[3];
# 18 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read.h" 1






unsigned int dimIN(int i,int j){
  return i + j*it[0];
}
unsigned int dimWAKE(int i,int j){
  return i + j*it[1];
}
unsigned int dimOUT(int i,int j){
  return i + j*it[2];
}




void *ealloc(size_t size){
  void *p;

  p = malloc(size);
  if(
# 24 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read.h" 3
    ((void *)0) 
# 24 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read.h"
         == p){
    perror("");
    exit(1);
  }

  return p;
}

void *memory(int n){
  void *p;
  p = ealloc(sizeof(double)*(it[n])*(jt[n]));
  return p;
}

void *memory_int(int n){
  void *p;
  p = ealloc(sizeof(int)*(it[n])*(jt[n]));
  return p;
}


void read(){
  int i, j, ij, n, r0, kk;
  char fn[50];
  FILE *fpw;

  sprintf(fn,"./grid/grid_data");

  fpw = fopen(fn, "r");
  if(
# 53 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read.h" 3
    ((void *)0) 
# 53 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read.h"
         == fpw){
    perror(fn);
    exit(1);
  }

  dim[0]=dimIN;
  dim[1]=dimWAKE;
  dim[2]=dimOUT;

  for(n=0;n<3;n++){
    fscanf(fpw,"%d %d\n",&it[n], &jt[n]);

    dG[n] = 1;
    dE[n] = it[n];

    printf("n:%d it:%d jt:%d Sij:%d\n",n,it[n],jt[n],it[n] * jt[n]);

    x_xi[n] = memory(n);
    y_xi[n] = memory(n);
    x_eta[n] = memory(n);
    y_eta[n] = memory(n);
    x_xi_cen[n] = memory(n);
    y_xi_cen[n] = memory(n);
    x_eta_cen[n] = memory(n);
    y_eta_cen[n] = memory(n);
    S[n] = memory(n);
    x[n] = memory(n);
    y[n] = memory(n);
    cen_x[n] = memory(n);
    cen_y[n] = memory(n);
    rho[n] = memory(n);
    ux[n] = memory(n);
    uy[n] = memory(n);
    p[n] = memory(n);
    e[n] = memory(n);
    d_wall[n] = memory(n);
    yp[n] = memory(n);
    Mut[n] = memory(n);
    NuSA[n] = memory(n);
    k_turb[n] = memory(n);
    omega[n] = memory(n);
    clx[n] = memory_int(n);
    cly[n] = memory_int(n);
    ut_buff[n] = memory(n);
    deruta_x[n] = memory(n);
    deruta_y[n] = memory(n);
    RA_LE[n] = memory(n);
    lkw[n] = memory(n);

    for(ij=0;ij<4;ij++){
      Q[n][ij] = memory(n);
      tmpQ[n][ij] = memory(n);
      E[n][ij] = memory(n);
      F[n][ij] = memory(n);
      Ev[n][ij] = memory(n);
      Fv[n][ij] = memory(n);
      tmpEE[n][ij] = memory(n);
      dQ[n][ij] = memory(n);
      rhsF[n][ij] = memory(n);
    }

    for(ij=0;ij<6;ij++){
      Ecen[n][ij] = memory(n);
      Fcen[n][ij] = memory(n);

      for(kk=0;kk<2;kk++){
 Qch[n][ij][kk] = memory(n);
 Qchcv[n][ij][kk] = memory(n);
      }
    }

    for(ij=0;ij<2;ij++){
      for(kk=0;kk<2;kk++){
 TurbQchcv[n][ij][kk] = memory(n);
      }
    }


    for(ij=0;ij<2;ij++){
      vis_S[n][ij] = memory(n);
      duxd[n][ij] = memory(n);
      duyd[n][ij] = memory(n);
      dcptd[n][ij] = memory(n);
      TurbE[n][ij] = memory(n);
      TurbF[n][ij] = memory(n);
      TurbEv[n][ij] = memory(n);
      TurbFv[n][ij] = memory(n);
      TurbQ[n][ij] = memory(n);
      TurbtmpQ[n][ij] = memory(n);
      TurbtmpEE[n][ij] = memory(n);
      TurbdQ[n][ij] = memory(n);
      rhsTurbF[n][ij] = memory(n);
    }


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 fscanf(fpw,"%lf %lf\n",&cen_x[n][r0], &cen_y[n][r0]);
      }
    }


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 fscanf(fpw,"%lf %lf %lf %lf %lf\n",&x_xi[n][r0], &y_xi[n][r0], &x_eta[n][r0], &y_eta[n][r0], &S[n][r0]);
      }
    }


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 fscanf(fpw,"%lf %lf %lf %lf\n",&x_xi_cen[n][r0], &y_xi_cen[n][r0], &x_eta_cen[n][r0], &y_eta_cen[n][r0]);
      }
    }


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 fscanf(fpw,"%lf\n",&d_wall[n][r0]);
      }
    }


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 fscanf(fpw,"%lf %lf\n",&deruta_x[n][r0], &deruta_y[n][r0]);
      }
    }

  }

  fclose(fpw);


}
# 19 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\calc.h" 1







inline double Cons_calcE(int n, int r1){
  return p[n][r1] / (1.4 - 1.0) + 0.5 * rho[n][r1] * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]);
}

inline double Cons_calcP(int n, int r1){
  return (1.4 - 1.0) * (e[n][r1] - 0.5 * rho[n][r1] * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]));
}

inline double Cons_calcH(int n, int r1){
  return (e[n][r1] + p[n][r1]) / rho[n][r1];
}

inline double Cons_calcCpT(int n, int r1){
  return (Cons_calcE(n, r1) + Cons_calcP(n, r1)) / rho[n][r1] - 0.5 * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]);
}

void Cons_tmp(){
  int n, i, j, r0;

  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 tmpQ[n][0][r0] = Q[n][0][r0];
 tmpQ[n][1][r0] = Q[n][1][r0];
 tmpQ[n][2][r0] = Q[n][2][r0];
 tmpQ[n][3][r0] = Q[n][3][r0];
 TurbtmpQ[n][0][r0] = TurbQ[n][0][r0];
 TurbtmpQ[n][1][r0] = TurbQ[n][1][r0];
      }
    }
  }


}
# 20 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\output.h" 1





void PostFlow_output(int time){
  char fn[50];
  FILE *fpw;
  int i, j, r0, n, xi, eta, ns, nv, ii;
  int Sij;
  int num;
  double mach, alp, re, Qt;
  int istep;


  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 Q[n][0][r0] = rho[n][r0] * S[n][r0];
 Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
 Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
 Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }
  }

  for(n=0;n<3;n++){
    sprintf(fn,"./out_wcns2/postFlow[%d][%d]",n,time);

    fpw = fopen(fn,"wb");

    if(
# 33 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\output.h" 3
      ((void *)0)
# 33 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\output.h"
          ==fpw){
      perror(fn);
      exit(1);
    }

    num = sizeof(int) * 2;
    xi = it[n] - 1;
    eta = jt[n] - 1;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&xi,sizeof(int),1,fpw);
    fwrite(&eta,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(double) * 3 + sizeof(int) * 1;
    mach = 0.0;
    alp = 0.0;
    re = 0.0;
    istep = 0;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&mach,sizeof(double),1,fpw);
    fwrite(&alp,sizeof(double),1,fpw);
    fwrite(&re,sizeof(double),1,fpw);
    fwrite(&istep,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);


    Sij = xi * eta;
    num = sizeof(double) * 4 * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    for(ii=0;ii<4;ii++){
      for(j=0;j<jt[n]-1;j++){
 for(i=0;i<it[n]-1;i++){
   r0 = dim[n](i, j);
   Qt = Q[n][ii][r0] / S[n][r0];
   fwrite(&Qt,sizeof(double),1,fpw);
 }
      }
    }
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(int) * 2;
    ns = 3;
    nv = 0;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&ns,sizeof(int),1,fpw);
    fwrite(&nv,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);

    Sij = xi * eta;
    num = sizeof(double) * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
     r0 = dim[n](i, j);
     fwrite(&k_turb[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
     r0 = dim[n](i, j);
     fwrite(&omega[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fwrite(&Mut[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(double) * nv * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);


    fclose(fpw);
  }

}
# 21 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read_data.h" 1
void PostFlow_input(int time){

  FILE *fpr;
  char fn[64];
  int i, j, r0, n, xi, eta, ns, nv;
  int Sij;
  int num;
  double mach, alp, re, Qt;
  int istep;

  for(n=0;n<3;n++){
    sprintf(fn,"./out_wcns2/postFlow[%d][%d]",n,time);
    fpr = fopen(fn,"rb");

    if(
# 15 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read_data.h" 3
      ((void *)0)
# 15 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\read_data.h"
          ==fpr){
      perror(fn);
      exit(1);
    }

    num = sizeof(int) * 2;
    xi = it[n] - 1;
    eta = jt[n] - 1;

    fread(&num,sizeof(int),1,fpr);
    fread(&xi,sizeof(int),1,fpr);
    fread(&eta,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);

    num = sizeof(double) * 3 + sizeof(int) * 1;
    mach = 0.0;
    alp = 0.0;
    re = 0.0;
    istep = 0;

    fread(&num,sizeof(int),1,fpr);
    fread(&mach,sizeof(double),1,fpr);
    fread(&alp,sizeof(double),1,fpr);
    fread(&re,sizeof(double),1,fpr);
    fread(&istep,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    Sij = xi * eta;
    num = sizeof(double) * 4 * Sij;

    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&rho[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&ux[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&uy[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&e[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);

    fread(&num,sizeof(int),1,fpr);
    fread(&ns,sizeof(int),1,fpr);
    fread(&nv,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&k_turb[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&omega[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
 r0 = dim[n](i, j);
 fread(&Mut[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);

    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    fclose(fpr);

  }

  for(n=0;n<3;n++){


    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 ux[n][r0] = ux[n][r0] / rho[n][r0];
 uy[n][r0] = uy[n][r0] / rho[n][r0];
 p[n][r0] = Cons_calcP(n, r0);
      }
    }



    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 Q[n][0][r0] = rho[n][r0] * S[n][r0];
 Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
 Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
 Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }

    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 TurbQ[n][0][r0] = rho[n][r0] * k_turb[n][r0] * S[n][r0];
 TurbQ[n][1][r0] = rho[n][r0] * omega[n][r0] * S[n][r0];
      }
    }
  }


}
# 22 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\initial.h" 1






void Initial(){
  int i, j, r0, n;
  double Re, nu, dX, ymin;
  double p_0, sita, rho_0, S_, T;
  double r, vr, vsita;
  double k1, k2;

  Re = (1.184 * 50.0 * 2.0 * 0.25) / 18.24e-6;
  dX = sqrt((cen_x[0][3] - cen_x[0][2]) * (cen_x[0][3] - cen_x[0][2]) + (cen_y[0][3] - cen_y[0][2]) * (cen_y[0][3] - cen_y[0][2]));
  nu = sqrt(1.4 * 101.325e+3 / 1.184) * 2.0e-6 / dX;
  ymin = 0.1 / sqrt(Re);
  printf("Re = %e\n",Re);
  printf("nu = %e\n",nu);
  printf("最小格子幅dr = %e\n",dX);
  printf("必要な最小格子幅(層流)ymin = %e\n",ymin);

  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 r = pow(cen_x[n][r0] ,2.0) + pow(cen_y[n][r0] ,2.0);
 sita = atan2(cen_y[n][r0],cen_x[n][r0]);
 vr = 50.0 * cos(sita) * (1.0 - 0.25 * 0.25 / r);
 vsita = 50.0 * sin(sita) * (1.0 + 0.25 * 0.25 / r);





 rho[n][r0] = 1.184;
 p[n][r0] = 101.325e+3 + 0.5 * 1.184 * 50.0 * 50.0 - 0.5 * 1.184 * (vr * vr + vsita * vsita);
 ux[n][r0] = (vr * cos(sita) + vsita * sin(sita));
 uy[n][r0] = (vr * sin(sita) - vsita * cos(sita));
 e[n][r0] = Cons_calcE(n, r0);

      }
    }
  }

  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 Q[n][0][r0] = rho[n][r0] * S[n][r0];
 Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
 Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
 Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }
  }

}
# 23 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\boundary.h" 1
# 13 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\boundary.h"
void wall_boundary(int n, int r0, int r1, int r2){
  double Mu, tmpT, w_wall;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * 287.04)) / 293.15;
  Mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);
  w_wall = 60.0 * Mu / (rho[n][r0] * 0.09 * pow(d_wall[n][r0], 2.0));

  p[n][r1] = p[n][r0];
  rho[n][r1] = rho[n][r0];
  ux[n][r1] = -ux[n][r0];
  uy[n][r1] = -uy[n][r0];
  e[n][r1] = Cons_calcE(n, r1);
  k_turb[n][r1] = - k_turb[n][r0];
  omega[n][r1] = 2.0 * w_wall - omega[n][r0];
  Mut[n][r1] = - Mut[n][r0];

  p[n][r2] = p[n][r1];
  rho[n][r2] = rho[n][r1];
  ux[n][r2] = ux[n][r1];
  uy[n][r2] = uy[n][r1];
  e[n][r2] = Cons_calcE(n, r2);
  k_turb[n][r2] = k_turb[n][r1];
  omega[n][r2] = omega[n][r1];
  Mut[n][r2] = Mut[n][r1];

}







void periodic_boundary(int n, int r0, int r1){
  p[n][r0] = p[n][r1];
  rho[n][r0] = rho[n][r1];
  ux[n][r0] = ux[n][r1];
  uy[n][r0] = uy[n][r1];
  e[n][r0] = Cons_calcE(n, r0);
  k_turb[n][r0] = k_turb[n][r1];
  omega[n][r0] = omega[n][r1];
  Mut[n][r0] = Mut[n][r1];
  RA_LE[n][r0] = RA_LE[n][r1];






}







void exit_boundary(int n, int r0, int r1){
  ux[n][r0] = ux[n][r1];
  uy[n][r0] = uy[n][r1];
  rho[n][r0] = 1.184;
  p[n][r0] = 101.325e+3;
  e[n][r0] = Cons_calcE(n, r0);
  k_turb[n][r0] = k_turb[n][r1];
  omega[n][r0] = omega[n][r1];
  Mut[n][r0] = Mut[n][r1];
}







void inter_boundary(int n, int r0, int r1){
  rho[n][r0] = 1.184;
  p[n][r0] = 101.325e+3;
  ux[n][r0] = 50.0;
  uy[n][r0] = 0.0;
  e[n][r0] = Cons_calcE(n, r0);
  k_turb[n][r0] = 1.0e-7 * 50.0 * 50.0;
  omega[n][r0] = 50.0 * 150 * 0.1;
  Mut[n][r0] = k_turb[n][r0] * rho[n][r0] / omega[n][r0];
}







void ukewatasi(int n0, int r0, int n1, int r1){
  p[n0][r0] = p[n1][r1];
  rho[n0][r0] = rho[n1][r1];
  ux[n0][r0] = ux[n1][r1];
  uy[n0][r0] = uy[n1][r1];
  e[n0][r0] = Cons_calcE(n0, r0);
  k_turb[n0][r0] = k_turb[n1][r1];
  omega[n0][r0] = omega[n1][r1];
  Mut[n0][r0] = Mut[n1][r1];
  RA_LE[n0][r0] = RA_LE[n1][r1];






}




inline static double Interpolation(double y0, double y1, double x0, double x1, double X){
  return y0 + (y1 - y0) * (X - x0) / (x1 - x0);
}





void interpolation_boundary(int n0, int r0, int n1, int j_n1){

  unsigned int i;
  int r1;
  int rn;
  double l;

  l = d_wall[n0][r0];

  for(i=2;i<it[n1]-1;i++){
    r1 = dim[n1](i, j_n1);
    rn = r1 + dG[n1];
    if( d_wall[n1][r1] <= l && l <= d_wall[n1][rn] ) { break; }
  }


  p[n0][r0] = Interpolation(p[n1][r1], p[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  rho[n0][r0] = Interpolation(rho[n1][r1], rho[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  ux[n0][r0] = Interpolation(ux[n1][r1], ux[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  uy[n0][r0] = Interpolation(uy[n1][r1], uy[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  e[n0][r0] = Cons_calcE(n0, r0);
  k_turb[n0][r0] = Interpolation(k_turb[n1][r1], k_turb[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  omega[n0][r0] = Interpolation(omega[n1][r1], omega[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  Mut[n0][r0] = Interpolation(Mut[n1][r1], Mut[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);






}


void boundary(){
  int i, j, r0, r1, r2, n, O_ini, O_end;
  double vr, vsita, r, p_0, rho_0, T, S_, k1, k2;
  double xi, sita;
  int n0, n1, n2;


  n = 0;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](2, j);
    r1 = dim[n](1, j);
    r2 = dim[n](0, j);
    wall_boundary(n, r0, r1, r2);
  }



  n = 1;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](it[n]-3, j);
    r1 = dim[n](it[n]-4, j);
    exit_boundary(n, r0, r1);

    r0 = dim[n](it[n]-2, j);
    r1 = dim[n](it[n]-3, j);
    exit_boundary(n, r0, r1);
  }


  n = 2;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](it[n]-3, j);
    r1 = dim[n](it[n]-4, j);
    inter_boundary(n, r0, r1);

    r0 = dim[n](it[n]-2, j);
    r1 = dim[n](it[n]-3, j);
    inter_boundary(n, r0, r1);
  }



  n = 0;
  for(i=0;i<it[n]-1;i++){
    r1 = dim[n](i, jt[n]-5);
    r0 = dim[n](i, 0);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, jt[n]-4);
    r0 = dim[n](i, 1);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, 2);
    r0 = dim[n](i, jt[n]-3);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, 3);
    r0 = dim[n](i, jt[n]-2);
    periodic_boundary(n, r0, r1);
  }


  n1 = 1;
  n2 = 2;
  for(i=2;i<it[n1]-3;i++){
    r1 = dim[n1](i, 0);
    interpolation_boundary(n1, r1, n2, jt[n2]-5);

    r1 = dim[n1](i, 1);
    interpolation_boundary(n1, r1, n2, jt[n2]-4);

    r1 = dim[n1](i, jt[n1]-3);
    interpolation_boundary(n1, r1, n2, 2);

    r1 = dim[n1](i, jt[n1]-2);
    interpolation_boundary(n1, r1, n2, 3);
  }

  for(i=2;i<it[n2]-3;i++){
    r2 = dim[n2](i, 0);
    interpolation_boundary(n2, r2, n1, jt[n1]-5);

    r2 = dim[n2](i, 1);
    interpolation_boundary(n2, r2, n1, jt[n1]-4);

    r2 = dim[n2](i, jt[n2]-3);
    interpolation_boundary(n2, r2, n1, 2);

    r2 = dim[n2](i, jt[n2]-2);
    interpolation_boundary(n2, r2, n1, 3);
  }



  n0 = 0;
  n1 = 1;
  for(j=0;j<jt[n0]-3-182;j++){
    r0 = dim[n0](it[n0]-5, 182 +j);
    r1 = dim[n1](0, j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-4, 182 +j);
    r1 = dim[n1](1, j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-3, 182 +j);
    r1 = dim[n1](2, j);
    ukewatasi(n0, r0, n1, r1);

    r0 = dim[n0](it[n0]-2, 182 +j);
    r1 = dim[n1](3, j);
    ukewatasi(n0, r0, n1, r1);
  }

  for(j=jt[n0]-3-182;j<jt[n1]-1;j++){
    r0 = dim[n0](it[n0]-5, j-65 +2);
    r1 = dim[n1](0, j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-4, j-65 +2);
    r1 = dim[n1](1, j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-3, j-65 +2);
    r1 = dim[n1](2, j);
    ukewatasi(n0, r0, n1, r1);

    r0 = dim[n0](it[n0]-2, j-65 +2);
    r1 = dim[n1](3, j);
    ukewatasi(n0, r0, n1, r1);
  }


  n0 = 0;
  n2 = 2;
  for(j=0;j<jt[n2]-1;j++){
    r0 = dim[n0](it[0]-5, 65 -2+j);
    r2 = dim[n2](0, j);
    ukewatasi(n2, r2, n0, r0);

    r0 = dim[n0](it[0]-4, 65 -2+j);
    r2 = dim[n2](1, j);
    ukewatasi(n2, r2, n0, r0);

    r0 = dim[n0](it[0]-3, 65 -2+j);
    r2 = dim[n2](2, j);
    ukewatasi(n0, r0, n2, r2);

    r0 = dim[n0](it[0]-2, 65 -2+j);
    r2 = dim[n2](3, j);
    ukewatasi(n0, r0, n2, r2);
  }


}
# 24 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2






# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\SST-DES.h" 1
# 82 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\SST-DES.h"
static double calc_komega_P(int n, int r0){
  double u_x, u_y;
  double v_x, v_y;
  double ux_e, ux_w, ux_n, ux_s;
  double uy_e, uy_w, uy_n, uy_s;
  int pG, mG, pE, mE;
  double PP, Sij;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  ux_e = 0.5 * (ux[n][pG] + ux[n][r0]);
  ux_w = 0.5 * (ux[n][mG] + ux[n][r0]);
  ux_n = 0.5 * (ux[n][pE] + ux[n][r0]);
  ux_s = 0.5 * (ux[n][mE] + ux[n][r0]);

  uy_e = 0.5 * (uy[n][pG] + uy[n][r0]);
  uy_w = 0.5 * (uy[n][mG] + uy[n][r0]);
  uy_n = 0.5 * (uy[n][pE] + uy[n][r0]);
  uy_s = 0.5 * (uy[n][mE] + uy[n][r0]);

  u_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (ux_e - ux_w) + (y_xi[n][pE] + y_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];
  v_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (uy_e - uy_w) + (y_xi[n][pE] + y_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];
  u_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (ux_e - ux_w) + (x_xi[n][pE] + x_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];
  v_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (uy_e - uy_w) + (x_xi[n][pE] + x_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];

  Sij = sqrt(2.0 * u_x * u_x + 2.0 * v_y * v_y + (u_y + v_x) * (u_y + v_x));

  PP = Mut[n][r0] * Sij * Sij;

  return PP;
}




static double calc_W(int n, int r0){
  double u_x, u_y;
  double v_x, v_y;
  double ux_e, ux_w, ux_n, ux_s;
  double uy_e, uy_w, uy_n, uy_s;
  int pG, mG, pE, mE;
  double W, Sij;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  ux_e = 0.5 * (ux[n][pG] + ux[n][r0]);
  ux_w = 0.5 * (ux[n][mG] + ux[n][r0]);
  ux_n = 0.5 * (ux[n][pE] + ux[n][r0]);
  ux_s = 0.5 * (ux[n][mE] + ux[n][r0]);

  uy_e = 0.5 * (uy[n][pG] + uy[n][r0]);
  uy_w = 0.5 * (uy[n][mG] + uy[n][r0]);
  uy_n = 0.5 * (uy[n][pE] + uy[n][r0]);
  uy_s = 0.5 * (uy[n][mE] + uy[n][r0]);

  v_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (uy_e - uy_w) + (y_xi[n][pE] + y_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];
  u_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (ux_e - ux_w) + (x_xi[n][pE] + x_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];

  W = sqrt((u_y - v_x) * (u_y - v_x));

  return W;
}





static double min2f(double xe,double ye){
  return (xe < ye ? xe : ye);
}




static double max2f(double xe,double ye){
  return (xe > ye ? xe : ye);
}





static double calc_derukw(int n, int r0){
  double k_x, k_y;
  double omega_x, omega_y;
  double k_e, k_w, k_n, k_s;
  double omega_e, omega_w, omega_n, omega_s;
  int pG, mG, pE, mE;
  double KW;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  k_e = 0.5 * (k_turb[n][pG] + k_turb[n][r0]);
  k_w = 0.5 * (k_turb[n][mG] + k_turb[n][r0]);
  k_n = 0.5 * (k_turb[n][pE] + k_turb[n][r0]);
  k_s = 0.5 * (k_turb[n][mE] + k_turb[n][r0]);

  omega_e = 0.5 * (omega[n][pG] + omega[n][r0]);
  omega_w = 0.5 * (omega[n][mG] + omega[n][r0]);
  omega_n = 0.5 * (omega[n][pE] + omega[n][r0]);
  omega_s = 0.5 * (omega[n][mE] + omega[n][r0]);

  k_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (k_e - k_w) + (y_xi[n][pE] + y_xi[n][r0]) * (k_n - k_s)) / S[n][r0];
  omega_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (omega_e - omega_w) + (y_xi[n][pE] + y_xi[n][r0]) * (omega_n - omega_s)) / S[n][r0];
  k_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (k_e - k_w) + (x_xi[n][pE] + x_xi[n][r0]) * (k_n - k_s)) / S[n][r0];
  omega_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (omega_e - omega_w) + (x_xi[n][pE] + x_xi[n][r0]) * (omega_n - omega_s)) / S[n][r0];

  KW = (k_x + k_y) * (omega_x + omega_y);

  return KW;
}





static double calc_F1(int n, int r0){
  double beta = 0.09;
  double tmpT, Mu, F1;
  double siguma_w2 = 0.856;
  double ans1, ans2, ans3, ans4, CDkw;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * 287.04)) / 293.15;
  Mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  CDkw = max2f(2.0 * rho[n][r0] * siguma_w2 * calc_derukw(n, r0) / omega[n][r0], 1.0e-20);

  ans1 = sqrt(k_turb[n][r0]) / (beta * omega[n][r0] * d_wall[n][r0]);
  ans2 = 500 * Mu / (rho[n][r0] * omega[n][r0] * pow(d_wall[n][r0], 2.0));
  ans3 = max2f(ans1, ans2);
  ans4 = 4.0 * siguma_w2 * k_turb[n][r0] / (CDkw * pow(d_wall[n][r0], 2.0));

  F1 = tanh(min2f(ans3, ans4));

  return F1;
}




static double calc_F2(int n, int r0){
  double beta = 0.09;
  double tmpT, Mu, F2;
  double ans1, ans2;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * 287.04)) / 293.15;
  Mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  ans1 = 2.0 * sqrt(k_turb[n][r0]) / (beta * omega[n][r0] * d_wall[n][r0]);
  ans2 = 500 * Mu / (rho[n][r0] * omega[n][r0] * pow(d_wall[n][r0], 2.0));

  F2 = tanh(pow(max2f(ans1, ans2) ,4.0));

  return F2;
}




static double calc_mix(int n, int r0, double var1, double var2){
  double F1;

  F1 = calc_F1(n, r0);

  return var1 * F1 + var2 * (1.0 - F1);
}




inline double calc_lkw(int n, int r0, double beta_star){
  return sqrt(k_turb[n][r0]) / (beta_star * omega[n][r0]);
}





void calc_komega(int n, int r0, double *RHSt){
  double PP, EE, D;
  const double beta_star = 0.09;
  const double beta_1 = 0.075;
  const double beta_2 = 0.0828;
  const double alpha_1 = 5.0 / 9.0;
  const double alpha_2 = 0.44;
  double siguma_w2 = 0.856;
  double alpha, beta, l_kw, deruta, l_DES, C_DES, fd, deruta_cor;

  alpha = calc_mix(n, r0, alpha_1, alpha_2);
  beta = calc_mix(n, r0, beta_1, beta_2);
  C_DES = calc_mix(n, r0, 0.78, 0.61);

  l_kw = calc_lkw(n, r0, beta_star);
  lkw[n][r0] = l_kw;
# 300 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\SST-DES.h"
  l_DES = l_kw;


  if(l_kw > l_DES){
    RA_LE[n][r0] = 0.0;
  }
  else{
    RA_LE[n][r0] = 1.0;
  }

  PP = calc_komega_P(n, r0);
  D = rho[n][r0] * pow(k_turb[n][r0], 1.5) / l_DES;
  EE = beta * rho[n][r0] * pow(omega[n][r0], 2.0);

  RHSt[0] = (PP - D) * S[n][r0];
  RHSt[1] = (alpha * rho[n][r0] * PP / Mut[n][r0] - EE + 2.0 * (1.0 - calc_F1(n, r0)) * rho[n][r0] * siguma_w2 * calc_derukw(n, r0) / omega[n][r0]) * S[n][r0];

}




void komega_ini(){
  int i, j, r0, n;
  double beta_1 = 0.075;
  double Mu, tmpT;
  double w_vis, w_log;
  double epsilon;

  for(n=0;n<3;n++){
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
 r0 = dim[n](i, j);

 k_turb[n][r0] = 1.0e-7 * 50.0 * 50.0 * 0.1;
 omega[n][r0] = 50.0 * 150 * 0.1;
 Mut[n][r0] = k_turb[n][r0] * rho[n][r0] / omega[n][r0];;
# 346 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\SST-DES.h"
      }
    }
  }

  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 TurbQ[n][0][r0] = rho[n][r0] * k_turb[n][r0] * S[n][r0];
 TurbQ[n][1][r0] = rho[n][r0] * omega[n][r0] * S[n][r0];
      }
    }
  }


}
# 31 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\fds.h" 1







void RIAIL(int n, int r0, double rho_s, double ux_s, double uy_s, double HH, double CC, int dz, double (*ral)[4]){
  double Right[4][4];
  double Left[4][4];
  double lambda_abs[4];

  double Jaco, kx, ky, Sk, kx_, ky_;
  double Z, Z_, QQ;
  double b1, b2;
  int ii, jj, kk;
  int dX, dY;
  int XI, ETA;

  XI = 0;
  ETA = 1;

  if(dz == XI){
    Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
    kx = y_eta[n][r0] * Jaco; ky = x_eta[n][r0] * Jaco;
  }
  else if(dz == ETA){
    Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
    kx = y_xi[n][r0] * Jaco; ky = x_xi[n][r0] * Jaco;
  }

  Sk = 1.0 / (sqrt(kx * kx + ky * ky));
  kx_ = kx * Sk;
  ky_ = ky * Sk;
  Z = kx * ux_s + ky * uy_s;
  Z_ = Z * Sk;
  QQ = ux_s * ux_s + uy_s * uy_s;

  lambda_abs[0] = fabs(Z - CC / Sk);
  lambda_abs[1] = fabs(Z );
  lambda_abs[2] = fabs(Z + CC / Sk);
  lambda_abs[3] = fabs(Z );

  Right[0][0] = 1.0;
  Right[0][1] = 1.0;
  Right[0][2] = 1.0;
  Right[0][3] = 0.0;
  Right[1][0] = ux_s - kx_ * CC;
  Right[1][1] = ux_s;
  Right[1][2] = ux_s + kx_ * CC;
  Right[1][3] = -ky_;
  Right[2][0] = uy_s - ky_ * CC;
  Right[2][1] = uy_s;
  Right[2][2] = uy_s + ky_ * CC;
  Right[2][3] = kx_;
  Right[3][0] = HH - CC * Z_;
  Right[3][1] = 0.5 * QQ;
  Right[3][2] = HH + CC * Z_;
  Right[3][3] = -(ky_ * ux_s - kx_ * uy_s);

  b1 = 0.5 * QQ * (1.4 - 1.0) / (CC * CC);
  b2 = (1.4 - 1.0) / (CC * CC);

  Left[0][0] = 0.5 * (b1 + Z_ / CC);
  Left[0][1] = -0.5 * (kx_ / CC + b2 * ux_s);
  Left[0][2] = -0.5 * (ky_ / CC + b2 * uy_s);
  Left[0][3] = 0.5 * b2;
  Left[1][0] = 1.0 - b1;
  Left[1][1] = b2 * ux_s;
  Left[1][2] = b2 * uy_s;
  Left[1][3] = -b2;
  Left[2][0] = 0.5 * (b1 - Z_ / CC);
  Left[2][1] = 0.5 * (kx_ / CC - b2 * ux_s);
  Left[2][2] = 0.5 * (ky_ / CC - b2 * uy_s);
  Left[2][3] = 0.5 * b2;
  Left[3][0] = ky_ * ux_s - kx_ * uy_s;
  Left[3][1] = -ky_;
  Left[3][2] = kx_;
  Left[3][3] = 0.0;

  for(ii=0;ii<4;ii++){
    for(jj=0;jj<4;jj++){
      ral[ii][jj] = 0.0;
      for(kk=0;kk<4;kk++){
 ral[ii][jj] += Right[ii][kk] * lambda_abs[kk] * Left[kk][jj];
      }
    }
  }

}

double minmod_limiter(double delt1,double delt2,double kk)
{
  double bb,result;

  bb = (3.0 - kk)/(1.0 - kk);
  if(delt1*delt2*bb<=0.0)
    {
      result = 0.0;
    }
  else if(fabs(delt1)/fabs(delt2*bb)<=1.0)
    {
      result = delt1;
    }
  else
    {
      result = delt2*bb;
    }
  return result;
}

void fds(){
  int n;

  for(n=0;n<3;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
 int r0;
 int pG, mG, mmG, ppG, mmmG;
 int dgd, jj;
 double invS;
 double p_r0, p_pG, p_ppG, p_mG, p_mmG, p_mmmG;
 double skx, sky, Jaco;

 double DD1rho, DD1ux, DD1uy, DD1p, DD1e, DD1k, DD1omega;
 double DD2rho, DD2ux, DD2uy, DD2p, DD2e, DD2k, DD2omega;
 double DD3rho, DD3ux, DD3uy, DD3p, DD3e, DD3k, DD3omega;
 double DD4rho, DD4ux, DD4uy, DD4p, DD4e, DD4k, DD4omega;
 double DD5rho, DD5ux, DD5uy, DD5p, DD5e, DD5k, DD5omega;

 double D1rho, D1ux, D1uy, D1p, D1e;
 double D2rho, D2ux, D2uy, D2p, D2e;
 double D3rho, D3ux, D3uy, D3p, D3e;

 double D1rho_, D1ux_, D1uy_, D1p_, D1e_;
 double D2rho_, D2ux_, D2uy_, D2p_, D2e_;
 double D3rho_, D3ux_, D3uy_, D3p_, D3e_;

 double rhoPG, uxPG, uyPG, pPG, cPG, ePG, VnPG;
 double rhoMG, uxMG, uyMG, pMG, cMG, eMG, VnMG;
 double rhoAVE,uxAVE,uyAVE,CCAVE,HHAVE;

 double RAL[4][4];
 double EE[4];
 double invrhoave;

 int XI, ETA;
 XI = 0;
 ETA = 1;


 double ipu = 1.0;
 double kk = 1.0/3.0;


 double ss = 1.0;

 r0 = dim[n](i, j);

 for(dgd=0;dgd<2;dgd++){
   if(dgd == XI){
     Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
     pG = r0 + dG[n];
     ppG = r0 + 2 * dG[n];
     mG = r0 - dG[n];
     mmG = r0 - 2 * dG[n];
     mmmG = r0 - 3 * dG[n];
     skx = y_eta[n][r0];
     sky = x_eta[n][r0];
   }
   else if(dgd == ETA){
     Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
     pG = r0 + dE[n];
     ppG = r0 + 2 * dE[n];
     mG = r0 - dE[n];
     mmG = r0 - 2 * dE[n];
     mmmG = r0 - 3 * dE[n];
     skx = y_xi[n][r0];
     sky = x_xi[n][r0];
   }

   if((i==2 && dgd==XI) || (j==2 && dgd==ETA) || (i==it[n]-3 && dgd==XI) || (j==jt[n]-3 && dgd==ETA)){
     p_r0 = Cons_calcP(n, r0);
     p_pG = Cons_calcP(n, pG);
     p_mG = Cons_calcP(n, mG);
     p_mmG = Cons_calcP(n, mmG);

     D1rho = rho[n][mG] - rho[n][mmG];
     D2rho = rho[n][r0] - rho[n][mG];
     D3rho = rho[n][pG] - rho[n][r0];
     D1ux = ux[n][mG] - ux[n][mmG];
     D2ux = ux[n][r0] - ux[n][mG];
     D3ux = ux[n][pG] - ux[n][r0];
     D1uy = uy[n][mG] - uy[n][mmG];
     D2uy = uy[n][r0] - uy[n][mG];
     D3uy = uy[n][pG] - uy[n][r0];
     D1e = e[n][mG] - e[n][mmG];
     D2e = e[n][r0] - e[n][mG];
     D3e = e[n][pG] - e[n][r0];
     D1p = p_mG - p_mmG;
     D2p = p_r0 - p_mG;
     D3p = p_pG - p_r0;
   }
   else{
     p_r0 = Cons_calcP(n, r0);
     p_pG = Cons_calcP(n, pG);
     p_ppG = Cons_calcP(n, ppG);
     p_mG = Cons_calcP(n, mG);
     p_mmG = Cons_calcP(n, mmG);
     p_mmmG = Cons_calcP(n, mmmG);

     DD1rho = rho[n][mmG] - rho[n][mmmG];
     DD2rho = rho[n][mG] - rho[n][mmG];
     DD3rho = rho[n][r0] - rho[n][mG];
     DD4rho = rho[n][pG] - rho[n][r0];
     DD5rho = rho[n][ppG] - rho[n][pG];
     DD1ux = ux[n][mmG] - ux[n][mmmG];
     DD2ux = ux[n][mG] - ux[n][mmG];
     DD3ux = ux[n][r0] - ux[n][mG];
     DD4ux = ux[n][pG] - ux[n][r0];
     DD5ux = ux[n][ppG] - ux[n][pG];
     DD1uy = uy[n][mmG] - uy[n][mmmG];
     DD2uy = uy[n][mG] - uy[n][mmG];
     DD3uy = uy[n][r0] - uy[n][mG];
     DD4uy = uy[n][pG] - uy[n][r0];
     DD5uy = uy[n][ppG] - uy[n][pG];
     DD1e = e[n][mmG] - e[n][mmmG];
     DD2e = e[n][mG] - e[n][mmG];
     DD3e = e[n][r0] - e[n][mG];
     DD4e = e[n][pG] - e[n][r0];
     DD5e = e[n][ppG] - e[n][pG];
     DD1p = p_mmG - p_mmmG;
     DD2p = p_mG - p_mmG;
     DD3p = p_r0 - p_mG;
     DD4p = p_pG - p_r0;
     DD5p = p_ppG - p_pG;

     D1rho = DD2rho - (minmod_limiter(DD3rho - DD2rho, DD2rho - DD1rho, kk) - minmod_limiter(DD2rho - DD1rho, DD3rho - DD2rho, kk)) / 6.0;
     D2rho = DD3rho - (minmod_limiter(DD4rho - DD3rho, DD3rho - DD2rho, kk) - minmod_limiter(DD3rho - DD2rho, DD4rho - DD3rho, kk)) / 6.0;
     D3rho = DD4rho - (minmod_limiter(DD5rho - DD4rho, DD4rho - DD3rho, kk) - minmod_limiter(DD4rho - DD3rho, DD5rho - DD4rho, kk)) / 6.0;
     D1ux = DD2ux - (minmod_limiter(DD3ux - DD2ux, DD2ux - DD1ux, kk) - minmod_limiter(DD2ux - DD1ux, DD3ux - DD2ux, kk)) / 6.0;
     D2ux = DD3ux - (minmod_limiter(DD4ux - DD3ux, DD3ux - DD2ux, kk) - minmod_limiter(DD3ux - DD2ux, DD4ux - DD3ux, kk)) / 6.0;
     D3ux = DD4ux - (minmod_limiter(DD5ux - DD4ux, DD4ux - DD3ux, kk) - minmod_limiter(DD4ux - DD3ux, DD5ux - DD4ux, kk)) / 6.0;
     D1uy = DD2uy - (minmod_limiter(DD3uy - DD2uy, DD2uy - DD1uy, kk) - minmod_limiter(DD2uy - DD1uy, DD3uy - DD2uy, kk)) / 6.0;
     D2uy = DD3uy - (minmod_limiter(DD4uy - DD3uy, DD3uy - DD2uy, kk) - minmod_limiter(DD3uy - DD2uy, DD4uy - DD3uy, kk)) / 6.0;
     D3uy = DD4uy - (minmod_limiter(DD5uy - DD4uy, DD4uy - DD3uy, kk) - minmod_limiter(DD4uy - DD3uy, DD5uy - DD4uy, kk)) / 6.0;
     D1p = DD2p - (minmod_limiter(DD3p - DD2p, DD2p - DD1p, kk) - minmod_limiter(DD2p - DD1p, DD3p - DD2p, kk)) / 6.0;
     D2p = DD3p - (minmod_limiter(DD4p - DD3p, DD3p - DD2p, kk) - minmod_limiter(DD3p - DD2p, DD4p - DD3p, kk)) / 6.0;
     D3p = DD4p - (minmod_limiter(DD5p - DD4p, DD4p - DD3p, kk) - minmod_limiter(DD4p - DD3p, DD5p - DD4p, kk)) / 6.0;
     D1e = DD2e - (minmod_limiter(DD3e - DD2e, DD2e - DD1e, kk) - minmod_limiter(DD2e - DD1e, DD3e - DD2e, kk)) / 6.0;
     D2e = DD3e - (minmod_limiter(DD4e - DD3e, DD3e - DD2e, kk) - minmod_limiter(DD3e - DD2e, DD4e - DD3e, kk)) / 6.0;
     D3e = DD4e - (minmod_limiter(DD5e - DD4e, DD4e - DD3e, kk) - minmod_limiter(DD4e - DD3e, DD5e - DD4e, kk)) / 6.0;
   }
# 280 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\fds.h"
   D1rho_ = minmod_limiter(D1rho, D2rho, kk);
   D2rho_ = minmod_limiter(D2rho, D1rho, kk);
   rhoMG = rho[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1rho_ + (1.0 + kk * ss) * D2rho_) * ipu;

   D1ux_ = minmod_limiter(D1ux, D2ux, kk);
   D2ux_ = minmod_limiter(D2ux, D1ux, kk);
   uxMG = ux[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1ux_ + (1.0 + kk * ss) * D2ux_) * ipu;

   D1uy_ = minmod_limiter(D1uy, D2uy, kk);
   D2uy_ = minmod_limiter(D2uy, D1uy, kk);
   uyMG = uy[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1uy_ + (1.0 + kk * ss) * D2uy_) * ipu;

   D1e_ = minmod_limiter(D1e, D2e, kk);
   D2e_ = minmod_limiter(D2e, D1e, kk);
   eMG = e[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1e_ + (1.0 + kk * ss) * D2e_) * ipu;

   D1p_ = minmod_limiter(D1p, D2p, kk);
   D2p_ = minmod_limiter(D2p, D1p, kk);
   pMG = p[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1p_ + (1.0 + kk * ss) * D2p_) * ipu;

   D3rho_ = minmod_limiter(D3rho, D2rho, kk);
   D2rho_ = minmod_limiter(D2rho, D3rho, kk);
   rhoPG = rho[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3rho_ + (1.0 + kk * ss) * D2rho_ ) * ipu;

   D3ux_ = minmod_limiter(D3ux, D2ux, kk);
   D2ux_ = minmod_limiter(D2ux, D3ux, kk);
   uxPG = ux[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3ux_ + (1.0 + kk * ss) * D2ux_ ) * ipu;

   D3uy_ = minmod_limiter(D3uy, D2uy, kk);
   D2uy_ = minmod_limiter(D2uy, D3uy, kk);
   uyPG = uy[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3uy_ + (1.0 + kk * ss) * D2uy_ ) * ipu;

   D3e_ = minmod_limiter(D3e, D2e, kk);
   D2e_ = minmod_limiter(D2e, D3e, kk);
   ePG = e[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3e_ + (1.0 + kk * ss) * D2e_ ) * ipu;

   D3p_ = minmod_limiter(D3p, D2p, kk);
   D2p_ = minmod_limiter(D2p, D3p, kk);
   pPG = p[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3p_ + (1.0 + kk * ss) * D2p_ ) * ipu;

   invrhoave = 1.0 / (sqrt(rhoPG) + sqrt(rhoMG));
   rhoAVE = sqrt(rhoPG * rhoMG);
   uxAVE = (sqrt(rhoPG) * uxPG + sqrt(rhoMG) * uxMG) * invrhoave;
   uyAVE = (sqrt(rhoPG) * uyPG + sqrt(rhoMG) * uyMG) * invrhoave;
   HHAVE = (sqrt(rhoPG) * (ePG + pPG) / rhoPG + sqrt(rhoMG) * (eMG + pMG) / rhoMG) * invrhoave;
   CCAVE = sqrt((1.4 - 1.0) * (HHAVE - 0.5 * (uxAVE * uxAVE + uyAVE * uyAVE)));

   RIAIL(n, r0, rhoAVE, uxAVE, uyAVE, HHAVE, CCAVE, dgd, RAL);

   VnMG = (uxMG * skx + uyMG * sky);
   VnPG = (uxPG * skx + uyPG * sky);

   EE[0] = rhoPG * VnPG + rhoMG * VnMG;
   EE[1] = rhoPG * uxPG * VnPG + skx * pPG + rhoMG * uxMG * VnMG + skx * pMG;
   EE[2] = rhoPG * uyPG * VnPG + sky * pPG + rhoMG * uyMG * VnMG + sky * pMG;
   EE[3] = VnPG * (ePG + pPG) + VnMG * (eMG + pMG);

   if(dgd == XI){
     for(jj=0;jj<=3;jj++){
       E[n][jj][r0] = 0.5 * (EE[jj] - (RAL[jj][0] * (rhoPG - rhoMG)
            + RAL[jj][1] * (uxPG * rhoPG - uxMG * rhoMG)
            + RAL[jj][2] * (uyPG * rhoPG - uyMG * rhoMG)
            + RAL[jj][3] * (ePG - eMG)) / Jaco);
     }
   }
   else if(dgd == ETA){
     for(jj=0;jj<=3;jj++){
       F[n][jj][r0] = 0.5 * (EE[jj] - (RAL[jj][0] * (rhoPG - rhoMG)
       + RAL[jj][1] * (uxPG * rhoPG - uxMG * rhoMG)
       + RAL[jj][2] * (uyPG * rhoPG - uyMG * rhoMG)
       + RAL[jj][3] * (ePG - eMG)) / Jaco);
     }
   }
 }
      }
    }
  }
}
# 32 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\fds-komega.h" 1






void fds_komega(){
  int n;

  for(n=0;n<3;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
 int r0;
 int pG, mG, mmG;
 double invS;
 int dgd, jj;
 double skx, sky, Jaco;
 double D1rho, D1ux, D1uy, D1k, D1omega;
 double D2rho, D2ux, D2uy, D2k, D2omega;
 double D3rho, D3ux, D3uy, D3k, D3omega;

 double D1rho_, D1ux_, D1uy_, D1k_, D1omega_;
 double D2rho_, D2ux_, D2uy_, D2k_, D2omega_;
 double D3rho_, D3ux_, D3uy_, D3k_, D3omega_;

 double rhoPG, uxPG, uyPG, kPG, omegaPG, VnPG;
 double rhoMG, uxMG, uyMG, kMG, omegaMG, VnMG;
 double rhoAVE,uxAVE,uyAVE,kAVE,omegaAVE;
 double UU;

 double EE[2];
 double RAL[2][2];
 double invrhoave;

 int XI, ETA;
 XI = 0;
 ETA = 1;


 double ipu = 1.0;
 double kk = 1.0/3.0;


 double ss = 1.0;

 r0 = dim[n](i, j);

 for(dgd=0;dgd<2;dgd++){
   if(dgd == XI){
     Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
     pG = r0 + dG[n];
     mG = r0 - dG[n];
     mmG = r0 - 2 * dG[n];
     skx = y_eta[n][r0];
     sky = x_eta[n][r0];
   }
   else if(dgd == ETA){
     Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
     pG = r0 + dE[n];
     mG = r0 - dE[n];
     mmG = r0 - 2 * dE[n];
     skx = y_xi[n][r0];
     sky = x_xi[n][r0];
   }

   D1rho = rho[n][mG] - rho[n][mmG];
   D2rho = rho[n][r0] - rho[n][mG];
   D3rho = rho[n][pG] - rho[n][r0];
   D1ux = ux[n][mG] - ux[n][mmG];
   D2ux = ux[n][r0] - ux[n][mG];
   D3ux = ux[n][pG] - ux[n][r0];
   D1uy = uy[n][mG] - uy[n][mmG];
   D2uy = uy[n][r0] - uy[n][mG];
   D3uy = uy[n][pG] - uy[n][r0];
   D1k = k_turb[n][mG] - k_turb[n][mmG];
   D2k = k_turb[n][r0] - k_turb[n][mG];
   D3k = k_turb[n][pG] - k_turb[n][r0];
   D1omega = omega[n][mG] - omega[n][mmG];
   D2omega = omega[n][r0] - omega[n][mG];
   D3omega = omega[n][pG] - omega[n][r0];

   D1rho_ = minmod_limiter(D1rho, D2rho, kk);
   D2rho_ = minmod_limiter(D2rho, D1rho, kk);
   rhoMG = rho[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1rho_ + (1.0 + kk * ss) * D2rho_) * ipu;

   D1ux_ = minmod_limiter(D1ux, D2ux, kk);
   D2ux_ = minmod_limiter(D2ux, D1ux, kk);
   uxMG = ux[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1ux_ + (1.0 + kk * ss) * D2ux_) * ipu;

   D1uy_ = minmod_limiter(D1uy, D2uy, kk);
   D2uy_ = minmod_limiter(D2uy, D1uy, kk);
   uyMG = uy[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1uy_ + (1.0 + kk * ss) * D2uy_) * ipu;

   D1k_ = minmod_limiter(D1k, D2k, kk);
   D2k_ = minmod_limiter(D2k, D1k, kk);
   kMG = k_turb[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1k_ + (1.0 + kk * ss) * D2k_) * ipu;

   D1omega_ = minmod_limiter(D1omega, D2omega, kk);
   D2omega_ = minmod_limiter(D2omega, D1omega, kk);
   omegaMG = omega[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1omega_ + (1.0 + kk * ss) * D2omega_) * ipu;

   D3rho_ = minmod_limiter(D3rho, D2rho, kk);
   D2rho_ = minmod_limiter(D2rho, D3rho, kk);
   rhoPG = rho[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3rho_ + (1.0 + kk * ss) * D2rho_ ) * ipu;

   D3ux_ = minmod_limiter(D3ux, D2ux, kk);
   D2ux_ = minmod_limiter(D2ux, D3ux, kk);
   uxPG = ux[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3ux_ + (1.0 + kk * ss) * D2ux_ ) * ipu;

   D3uy_ = minmod_limiter(D3uy, D2uy, kk);
   D2uy_ = minmod_limiter(D2uy, D3uy, kk);
   uyPG = uy[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3uy_ + (1.0 + kk * ss) * D2uy_ ) * ipu;

   D3k_ = minmod_limiter(D3k, D2k, kk);
   D2k_ = minmod_limiter(D2k, D3k, kk);
   kPG = k_turb[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3k_ + (1.0 + kk * ss) * D2k_ ) * ipu;

   D3omega_ = minmod_limiter(D3omega, D2omega, kk);
   D2omega_ = minmod_limiter(D2omega, D3omega, kk);
   omegaPG = omega[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3omega_ + (1.0 + kk * ss) * D2omega_ ) * ipu;

   invrhoave = 1.0 / (sqrt(rhoPG) + sqrt(rhoMG));
   rhoAVE = sqrt(rhoPG * rhoMG);
   uxAVE = (sqrt(rhoPG) * uxPG + sqrt(rhoMG) * uxMG) * invrhoave;
   uyAVE = (sqrt(rhoPG) * uyPG + sqrt(rhoMG) * uyMG) * invrhoave;
   kAVE = (sqrt(rhoPG) * kPG + sqrt(rhoMG) * kMG) * invrhoave;
   omegaAVE = (sqrt(rhoPG) * omegaPG + sqrt(rhoMG) * omegaMG) * invrhoave;


   VnMG = (uxMG * skx + uyMG * sky);
   VnPG = (uxPG * skx + uyPG * sky);

   EE[0] = rhoPG * kPG * VnPG + rhoMG * kMG * VnMG;
   EE[1] = rhoPG * omegaPG * VnPG + rhoMG * omegaMG * VnMG;

   UU = (skx * uxAVE + sky * uyAVE) * Jaco;

   RAL[0][0] = fabs(UU);
   RAL[0][1] = 0.0;
   RAL[1][0] = 0.0;
   RAL[1][1] = fabs(UU);


   if(dgd == XI){
     for(jj=0;jj<=1;jj++){
       TurbE[n][jj][r0] = 0.5 * (EE[jj] - (RAL[jj][0] * (rhoPG * kPG - rhoMG * kMG)
         + RAL[jj][1] * (rhoPG * omegaPG - rhoMG * omegaMG)) / Jaco);
     }
   }
   else if(dgd == ETA){
     for(jj=0;jj<=1;jj++){
       TurbF[n][jj][r0] = 0.5 * (EE[jj] - (RAL[jj][0] * (rhoPG * kPG - rhoMG * kMG)
         + RAL[jj][1] * (rhoPG * omegaPG - rhoMG * omegaMG)) / Jaco);
     }
   }
 }
      }
    }
  }




}
# 33 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2

# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\viscous.h" 1
# 9 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\viscous.h"
void Viscous_calc_xi(int n, int r0){
  double mu, Mueff, Mut_xi;
  double tmpT;
  double T_1;
  double T_2;
  double T_3;
  double T_4;
  double T_5;
  double T_6;
  double Txx;
  double Txy;
  double Tyy;
  double Tx;
  double Ty;
  double u_x;
  double u_y;
  double v_x;
  double v_y;
  double u_ave1;
  double u_ave2;
  double v_ave1;
  double v_ave2;
  double kx, ky, Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x, xi_y;
  double eta_x1, eta_y1, eta_x2, eta_y2, eta_x3, eta_y3, eta_x4, eta_y4;
  double betax, betay;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dG[n];
  r2 = r0 - dG[n] + dE[n];
  r3 = r0 - dG[n] - dE[n];
  r4 = r0 + dE[n];
  r5 = r0 - dE[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx = y_eta[n][r0];
  ky = x_eta[n][r0];
  xi_x = y_eta[n][r0] * Jaco0;
  xi_y = x_eta[n][r0] * Jaco0;
  eta_x1 = y_xi[n][r2] * Jaco1;
  eta_y1 = x_xi[n][r2] * Jaco1;
  eta_x2 = y_xi[n][r1] * Jaco2;
  eta_y2 = x_xi[n][r1] * Jaco2;
  eta_x3 = y_xi[n][r4] * Jaco3;
  eta_y3 = x_xi[n][r4] * Jaco3;
  eta_x4 = y_xi[n][r0] * Jaco4;
  eta_y4 = x_xi[n][r0] * Jaco4;



  T_1 = Cons_calcCpT(n, r1);
  T_2 = Cons_calcCpT(n, r0);
  T_3 = Cons_calcCpT(n, r2);
  T_4 = Cons_calcCpT(n, r3);
  T_5 = Cons_calcCpT(n, r4);
  T_6 = Cons_calcCpT(n, r5);

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * 287.04) + Cons_calcP(n, r1) / (rho[n][r1] * 287.04)) / 293.15;
  mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  Mueff = mu + 0.5 * (Mut[n][r0] + Mut[n][r1]);
  Mut_xi = 0.5 * (Mut[n][r0] + Mut[n][r1]);

  u_x = xi_x * (ux[n][r0] - ux[n][r1]) + 0.25 * (eta_x1 * (ux[n][r2] - ux[n][r1])
            + eta_x2 * (ux[n][r1] - ux[n][r3])
            + eta_x3 * (ux[n][r4] - ux[n][r0])
            + eta_x4 * (ux[n][r0] - ux[n][r5]));

  v_x = xi_x * (uy[n][r0] - uy[n][r1]) + 0.25 * (eta_x1 * (uy[n][r2] - uy[n][r1])
            + eta_x2 * (uy[n][r1] - uy[n][r3])
            + eta_x3 * (uy[n][r4] - uy[n][r0])
            + eta_x4 * (uy[n][r0] - uy[n][r5]));


  u_y = xi_y * (ux[n][r0] - ux[n][r1]) + 0.25 * (eta_y1 * (ux[n][r2] - ux[n][r1])
            + eta_y2 * (ux[n][r1] - ux[n][r3])
            + eta_y3 * (ux[n][r4] - ux[n][r0])
            + eta_y4 * (ux[n][r0] - ux[n][r5]));

  v_y = xi_y * (uy[n][r0] - uy[n][r1]) + 0.25 * (eta_y1 * (uy[n][r2] - uy[n][r1])
            + eta_y2 * (uy[n][r1] - uy[n][r3])
            + eta_y3 * (uy[n][r4] - uy[n][r0])
            + eta_y4 * (uy[n][r0] - uy[n][r5]));


  Tx = xi_x * (T_2 - T_1) + 0.25 * (eta_x1 * (T_3 - T_1) + eta_x2 * (T_1 - T_4) + eta_x3 * (T_5 - T_2) + eta_x4 * (T_2 - T_6));
  Ty = xi_y * (T_2 - T_1) + 0.25 * (eta_y1 * (T_3 - T_1) + eta_y2 * (T_1 - T_4) + eta_y3 * (T_5 - T_2) + eta_y4 * (T_2 - T_6));

  Txx = 2.0 * Mueff * (2.0 * u_x - v_y) / 3.0;
  Txy = Mueff * (u_y + v_x);
  Tyy = 2.0 * Mueff * (2.0 * v_y - u_x) / 3.0;
  betax = Txx * (ux[n][r1] + ux[n][r0]) * 0.5 + Txy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / 0.72 + Mut_xi / 0.9) * Tx;
  betay = Txy * (ux[n][r1] + ux[n][r0]) * 0.5 + Tyy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / 0.72 + Mut_xi / 0.9) * Ty;

  Ev[n][0][r0] = 0.0;
  Ev[n][1][r0] = kx * Txx + ky * Txy;
  Ev[n][2][r0] = kx * Txy + ky * Tyy;
  Ev[n][3][r0] = kx * betax + ky * betay;

}

void Viscous_calc_eta(int n, int r0){
  double mu, Mueff, Mut_eta;
  double tmpT;
  double T_1;
  double T_2;
  double T_3;
  double T_4;
  double T_5;
  double T_6;
  double Txx;
  double Txy;
  double Tyy;
  double Tx;
  double Ty;
  double u_x;
  double u_y;
  double v_x;
  double v_y;
  double u_ave1;
  double u_ave2;
  double v_ave1;
  double v_ave2;
  double kx, ky, Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x1, xi_y1, xi_x2, xi_y2, xi_x3, xi_y3, xi_x4, xi_y4;
  double eta_x, eta_y;
  double betax, betay;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dE[n];
  r2 = r0 - dE[n] - dG[n];
  r3 = r0 - dE[n] + dG[n];
  r4 = r0 - dG[n];
  r5 = r0 + dG[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx = y_xi[n][r0];
  ky = x_xi[n][r0];
  eta_x = y_xi[n][r0] * Jaco0;
  eta_y = x_xi[n][r0] * Jaco0;
  xi_x1 = y_eta[n][r1] * Jaco1;
  xi_y1 = x_eta[n][r1] * Jaco1;
  xi_x2 = y_eta[n][r3] * Jaco2;
  xi_y2 = x_eta[n][r3] * Jaco2;
  xi_x3 = y_eta[n][r0] * Jaco3;
  xi_y3 = x_eta[n][r0] * Jaco3;
  xi_x4 = y_eta[n][r5] * Jaco4;
  xi_y4 = x_eta[n][r5] * Jaco4;



  T_1 = Cons_calcCpT(n, r1);
  T_2 = Cons_calcCpT(n, r0);
  T_3 = Cons_calcCpT(n, r2);
  T_4 = Cons_calcCpT(n, r4);
  T_5 = Cons_calcCpT(n, r3);
  T_6 = Cons_calcCpT(n, r5);

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * 287.04) + Cons_calcP(n, r1) / (rho[n][r1] * 287.04)) / 293.15;
  mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  Mueff = mu + 0.5 * (Mut[n][r0] + Mut[n][r1]);
  Mut_eta = 0.5 * (Mut[n][r0] + Mut[n][r1]);

  u_x = eta_x * (ux[n][r0] - ux[n][r1]) + 0.25 * (xi_x1 * (ux[n][r1] - ux[n][r2])
      + xi_x2 * (ux[n][r3] - ux[n][r1])
             + xi_x3 * (ux[n][r0] - ux[n][r4])
      + xi_x4 * (ux[n][r5] - ux[n][r0]));

  v_x = eta_x * (uy[n][r0] - uy[n][r1]) + 0.25 * (xi_x1 * (uy[n][r1] - uy[n][r2])
                    + xi_x2 * (uy[n][r3] - uy[n][r1])
             + xi_x3 * (uy[n][r0] - uy[n][r4])
             + xi_x4 * (uy[n][r5] - uy[n][r0]));


  u_y = eta_y * (ux[n][r0] - ux[n][r1]) + 0.25 * (xi_y1 * (ux[n][r1] - ux[n][r2])
             + xi_y2 * (ux[n][r3] - ux[n][r1])
             + xi_y3 * (ux[n][r0] - ux[n][r4])
             + xi_y4 * (ux[n][r5] - ux[n][r0]));


  v_y = eta_y * (uy[n][r0] - uy[n][r1]) + 0.25 * (xi_y1 * (uy[n][r1] - uy[n][r2])
             + xi_y2 * (uy[n][r3] - uy[n][r1])
             + xi_y3 * (uy[n][r0] - uy[n][r4])
             + xi_y4 * (uy[n][r5] - uy[n][r0]));


  Tx = eta_x * (T_2 - T_1) + 0.25 * (xi_x1 * (T_1 - T_3) + xi_x2 * (T_5 - T_1) + xi_x3 * (T_2 - T_4) + xi_x4 * (T_6 - T_2));
  Ty = eta_y * (T_2 - T_1) + 0.25 * (xi_y1 * (T_1 - T_3) + xi_y2 * (T_5 - T_1) + xi_y3 * (T_2 - T_4) + xi_y4 * (T_6 - T_2));


  Txx = 2.0 * Mueff * (2.0 * u_x - v_y) / 3.0;
  Txy = Mueff * (u_y + v_x);
  Tyy = 2.0 * Mueff * (2.0 * v_y - u_x) / 3.0;
  betax = Txx * (ux[n][r1] + ux[n][r0]) * 0.5 + Txy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / 0.72 + Mut_eta / 0.9) * Tx;
  betay = Txy * (ux[n][r1] + ux[n][r0]) * 0.5 + Tyy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / 0.72 + Mut_eta / 0.9) * Ty;

  Fv[n][0][r0] = 0.0;
  Fv[n][1][r0] = kx * Txx + ky * Txy;
  Fv[n][2][r0] = kx * Txy + ky * Tyy;
  Fv[n][3][r0] = kx * betax + ky * betay;
}

void viscous(){
  int n;

  for(n=0;n<3;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
 int r0;
 r0 = dim[n](i, j);
 Viscous_calc_xi(n, r0);
 Viscous_calc_eta(n, r0);
      }
    }
  }

}
# 35 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\viscous-SST.h" 1







void Viscous_komega_xi(int n, int r0){
  const double siguma_k_1 = 0.85;
  const double siguma_k_2 = 1.0;
  const double siguma_omega_1 = 0.5;
  const double siguma_omega_2 = 0.856;
  double siguma_k;
  double siguma_omega;
  double kx, ky;
  double kturb_x, kturb_y;
  double omega_x, omega_y;
  double Mu, Mueff_k, Mueff_omega;
  double Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x, xi_y;
  double eta_x1, eta_y1, eta_x2, eta_y2, eta_x3, eta_y3, eta_x4, eta_y4;
  double tmpT;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dG[n];
  r2 = r0 - dG[n] + dE[n];
  r3 = r0 - dG[n] - dE[n];
  r4 = r0 + dE[n];
  r5 = r0 - dE[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx = y_eta[n][r0];
  ky = x_eta[n][r0];
  xi_x = y_eta[n][r0] * Jaco0;
  xi_y = x_eta[n][r0] * Jaco0;
  eta_x1 = y_xi[n][r2] * Jaco1;
  eta_y1 = x_xi[n][r2] * Jaco1;
  eta_x2 = y_xi[n][r1] * Jaco2;
  eta_y2 = x_xi[n][r1] * Jaco2;
  eta_x3 = y_xi[n][r4] * Jaco3;
  eta_y3 = x_xi[n][r4] * Jaco3;
  eta_x4 = y_xi[n][r0] * Jaco4;
  eta_y4 = x_xi[n][r0] * Jaco4;

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * 287.04) + Cons_calcP(n, r1) / (rho[n][r1] * 287.04)) / 293.15;
  Mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  siguma_k = calc_mix(n, r0, siguma_k_1, siguma_k_2);
  siguma_omega = calc_mix(n, r0, siguma_omega_1, siguma_omega_2);

  Mueff_k = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_k;
  Mueff_omega = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_omega;

  kturb_x = xi_x * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (eta_x1 * (k_turb[n][r2] - k_turb[n][r1])
                     + eta_x2 * (k_turb[n][r1] - k_turb[n][r3])
                     + eta_x3 * (k_turb[n][r4] - k_turb[n][r0])
                     + eta_x4 * (k_turb[n][r0] - k_turb[n][r5]));

  omega_x = xi_x * (omega[n][r0] - omega[n][r1]) + 0.25 * (eta_x1 * (omega[n][r2] - omega[n][r1])
                   + eta_x2 * (omega[n][r1] - omega[n][r3])
                   + eta_x3 * (omega[n][r4] - omega[n][r0])
                   + eta_x4 * (omega[n][r0] - omega[n][r5]));


  kturb_y = xi_y * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (eta_y1 * (k_turb[n][r2] - k_turb[n][r1])
                     + eta_y2 * (k_turb[n][r1] - k_turb[n][r3])
                     + eta_y3 * (k_turb[n][r4] - k_turb[n][r0])
                     + eta_y4 * (k_turb[n][r0] - k_turb[n][r5]));

  omega_y = xi_y * (omega[n][r0] - omega[n][r1]) + 0.25 * (eta_y1 * (omega[n][r2] - omega[n][r1])
                   + eta_y2 * (omega[n][r1] - omega[n][r3])
                   + eta_y3 * (omega[n][r4] - omega[n][r0])
                   + eta_y4 * (omega[n][r0] - omega[n][r5]));

  TurbEv[n][0][r0] = kx * Mueff_k * kturb_x + ky * Mueff_k * kturb_y;
  TurbEv[n][1][r0] = kx * Mueff_omega * omega_x + ky * Mueff_omega * omega_y;
}

void Viscous_komega_eta(int n, int r0){
  const double siguma_k_1 = 0.85;
  const double siguma_k_2 = 1.0;
  const double siguma_omega_1 = 0.5;
  const double siguma_omega_2 = 0.856;
  double siguma_k;
  double siguma_omega;
  double kx, ky;
  double kturb_x, kturb_y;
  double omega_x, omega_y;
  double Mu, Mueff_k, Mueff_omega;
  double Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x1, xi_y1, xi_x2, xi_y2, xi_x3, xi_y3, xi_x4, xi_y4;
  double eta_x, eta_y;
  double tmpT;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dE[n];
  r2 = r0 - dE[n] - dG[n];
  r3 = r0 - dE[n] + dG[n];
  r4 = r0 - dG[n];
  r5 = r0 + dG[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx = y_xi[n][r0];
  ky = x_xi[n][r0];
  eta_x = y_xi[n][r0] * Jaco0;
  eta_y = x_xi[n][r0] * Jaco0;
  xi_x1 = y_eta[n][r1] * Jaco1;
  xi_y1 = x_eta[n][r1] * Jaco1;
  xi_x2 = y_eta[n][r3] * Jaco2;
  xi_y2 = x_eta[n][r3] * Jaco2;
  xi_x3 = y_eta[n][r0] * Jaco3;
  xi_y3 = x_eta[n][r0] * Jaco3;
  xi_x4 = y_eta[n][r5] * Jaco4;
  xi_y4 = x_eta[n][r5] * Jaco4;

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * 287.04) + Cons_calcP(n, r1) / (rho[n][r1] * 287.04)) / 293.15;
  Mu = 18.24e-6 * tmpT * sqrt(tmpT) * (1.0 + 110.4 / 293.15) / (tmpT + 110.4 / 293.15);

  siguma_k = calc_mix(n, r0, siguma_k_1, siguma_k_2);
  siguma_omega = calc_mix(n, r0, siguma_omega_1, siguma_omega_2);

  Mueff_k = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_k;
  Mueff_omega = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_omega;

  kturb_x = eta_x * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (xi_x1 * (k_turb[n][r1] - k_turb[n][r2])
                      + xi_x2 * (k_turb[n][r3] - k_turb[n][r1])
                      + xi_x3 * (k_turb[n][r0] - k_turb[n][r4])
                      + xi_x4 * (k_turb[n][r5] - k_turb[n][r0]));

  omega_x = eta_x * (omega[n][r0] - omega[n][r1]) + 0.25 * (xi_x1 * (omega[n][r1] - omega[n][r2])
                    + xi_x2 * (omega[n][r3] - omega[n][r1])
                    + xi_x3 * (omega[n][r0] - omega[n][r4])
                    + xi_x4 * (omega[n][r5] - omega[n][r0]));


  kturb_y = eta_y * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (xi_y1 * (k_turb[n][r1] - k_turb[n][r2])
                      + xi_y2 * (k_turb[n][r3] - k_turb[n][r1])
                      + xi_y3 * (k_turb[n][r0] - k_turb[n][r4])
                      + xi_y4 * (k_turb[n][r5] - k_turb[n][r0]));


  omega_y = eta_y * (omega[n][r0] - omega[n][r1]) + 0.25 * (xi_y1 * (omega[n][r1] - omega[n][r2])
                    + xi_y2 * (omega[n][r3] - omega[n][r1])
                    + xi_y3 * (omega[n][r0] - omega[n][r4])
                    + xi_y4 * (omega[n][r5] - omega[n][r0]));

  TurbFv[n][0][r0] = kx * Mueff_k * kturb_x + ky * Mueff_k * kturb_y;
  TurbFv[n][1][r0] = kx * Mueff_omega * omega_x + ky * Mueff_omega * omega_y;
}

void viscous_komega(){
  int n;

  for(n=0;n<3;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
 int r0;
 r0 = dim[n](i, j);
 Viscous_komega_xi(n, r0);
 Viscous_komega_eta(n, r0);
      }
    }
  }

}
# 36 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2

# 1 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 1
# 11 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
static void calcPM(int rr,int n,int pmflag,int ddg,int dde,double **qq,double **turbqq,double (*flux)[6],double (*spe))
{
  int ii;
  double ZZ,ZZ0,invQ,kx,ky,kz,Sk,c;
  double Jacort, Jacork, Jaco;
  int rt, rk, rmet;
  int mflag;
  int ddd[2];
  int XI = 0;
  int ETA = 1;
  int X = 0;
  int Y = 1;
  double *SS[2][2];
  double tmpux ,tmpuy,tmprho,tmpp,tmpe,tmpk,tmpomega;
  double tmp,Mu;
  double ALPHA = 1.01;


  ddd[XI] = ddg;
  ddd[ETA] = dde;

  SS[XI][X] = y_eta[n];
  SS[ETA][X] = y_xi[n];

  SS[XI][Y] = x_eta[n];
  SS[ETA][Y] = x_xi[n];

  for(mflag=0;mflag<2;mflag++)
    {

      rt = rr;
      rk = rt + pmflag * ddd[mflag];
      rmet = rr;

      if(pmflag==1){
 rmet = rk;
      }

      if(qq[0][rt]!=0.0)
       {
   Jaco = 2.0 / (S[n][rt] + S[n][rk]);
   Jacort = 1.0 / S[n][rt];
   Jacork = 1.0 / S[n][rk];

   kx = SS[mflag][X][rmet] * Jaco;
   ky = SS[mflag][Y][rmet] * Jaco;

   Sk = ( sqrt( kx*kx + ky*ky ) );

   invQ = 1.0 / (qq[0][rk] + rho[n][rt] * S[n][rt]);
   tmprho = (qq[0][rk] * Jacork + rho[n][rt]);
   tmpux = (qq[1][rk] + ux[n][rt] * rho[n][rt] * S[n][rt])*invQ;
   tmpuy = (qq[2][rk] + uy[n][rt] * rho[n][rt] * S[n][rt])*invQ;
   tmpe = (qq[3][rk] * Jacork + e[n][rt]);
   tmpk = (turbqq[0][rk] + k_turb[n][rt] * rho[n][rt] * S[n][rt])*invQ;
   tmpomega = (turbqq[1][rk] + omega[n][rt] * rho[n][rt] * S[n][rt])*invQ;
   tmpp = (1.4 - 1.0) * (tmpe - 0.5 * tmprho * (tmpux*tmpux+tmpuy*tmpuy) );

   ZZ = (kx * tmpux + ky * tmpuy);
   ZZ0 = 0.5 * (kx* (ux[n][rt] + ux[n][rk]) + ky* (uy[n][rt] + uy[n][rk]));
   c = sqrt( 1.4 * Cons_calcP(n, rt) / rho[n][rt]);
   tmp = Cons_calcP(n , rt) / rho[n][rt] / 287.04;
   Mu = 18.24e-6 * ( pow((tmp)/(273.15+20.0),1.5) * (273.15+20.0 + 110.4)/(tmp + 110.4));


   spe[mflag]= fabs(ZZ0) + c*Sk + 2.0*(Mu+Mut[n][rt])*Sk*Sk/rho[n][rt];






   flux[mflag][0] = 0.5*((tmprho*ZZ)/Jaco - pmflag * spe[mflag] * qq[0][rk]);
   flux[mflag][1] = 0.5*((tmprho*tmpux*ZZ + kx*tmpp)/Jaco - pmflag * spe[mflag] * qq[1][rk]);
   flux[mflag][2] = 0.5*((tmprho*tmpuy*ZZ + ky*tmpp)/Jaco - pmflag * spe[mflag] * qq[2][rk]);
   flux[mflag][3] = 0.5*(((tmpe+tmpp)*ZZ)/Jaco - pmflag * spe[mflag] * qq[3][rk]);
   flux[mflag][4] = 0.5*((tmprho*tmpk*ZZ)/Jaco - pmflag * spe[mflag] * turbqq[0][rk]);
   flux[mflag][5] = 0.5*((tmprho*tmpomega*ZZ)/Jaco - pmflag * spe[mflag] * turbqq[1][rk]);
 }
      else{
       flux[mflag][0] =0.0;
       flux[mflag][1] =0.0;
       flux[mflag][2] =0.0;
       flux[mflag][3] =0.0;
       flux[mflag][4] =0.0;
       flux[mflag][5] =0.0;
      }
    }

}


void dQ_Initial(){
  int n, r0, i, j;

  for(n=0;n<3;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
 r0 = dim[n](i, j);
 dQ[n][0][r0] = 0.0;
 dQ[n][1][r0] = 0.0;
 dQ[n][2][r0] = 0.0;
 dQ[n][3][r0] = 0.0;
 TurbdQ[n][0][r0] = 0.0;
 TurbdQ[n][1][r0] = 0.0;

 rhsF[n][0][r0] = 0.0;
 rhsF[n][1][r0] = 0.0;
 rhsF[n][2][r0] = 0.0;
 rhsF[n][3][r0] = 0.0;
 rhsTurbF[n][0][r0] = 0.0;
 rhsTurbF[n][1][r0] = 0.0;
      }
    }
  }

}

void gauss_seidel(int time){
  int itr, n, ii, jj, kk, nn, numk, t;
  double errormax;
  double error4;

  itr = 0;

  dQ_Initial();

  for(itr=0;itr<2;itr++){

    fds();



    viscous();
    viscous_komega();


    ii = jj = kk = 0;
    errormax = 0.0;


    for(n=0;n<3;n++){
      int i, j, r0;






#pragma omp for private(i, j, r0)
 for(j=2;j<jt[n]-3;j++){
   for(i=2;i<it[n]-3;i++){
     double Jaco, invQ;
     double RHS0, RHS1, RHS2, RHS3, RHS4, RHS5, RHSt[2];
     double spe_r0[2];
     double spe_rt[2];
     double deltaFlux[2][6];
     double rhs1[6];
     double LDinv;
     int XI = 0;
     int ETA = 1;

     r0 = dim[n](i, j);

     RHS0 = - 2.0e-6 * ((E[n][0][r0+dG[n]] - E[n][0][r0]) - (Ev[n][0][r0+dG[n]] - Ev[n][0][r0]) + (F[n][0][r0+dE[n]] - F[n][0][r0]) - (Fv[n][0][r0+dE[n]] - Fv[n][0][r0]));
     RHS1 = - 2.0e-6 * ((E[n][1][r0+dG[n]] - E[n][1][r0]) - (Ev[n][1][r0+dG[n]] - Ev[n][1][r0]) + (F[n][1][r0+dE[n]] - F[n][1][r0]) - (Fv[n][1][r0+dE[n]] - Fv[n][1][r0]));
     RHS2 = - 2.0e-6 * ((E[n][2][r0+dG[n]] - E[n][2][r0]) - (Ev[n][2][r0+dG[n]] - Ev[n][2][r0]) + (F[n][2][r0+dE[n]] - F[n][2][r0]) - (Fv[n][2][r0+dE[n]] - Fv[n][2][r0]));
     RHS3 = - 2.0e-6 * ((E[n][3][r0+dG[n]] - E[n][3][r0]) - (Ev[n][3][r0+dG[n]] - Ev[n][3][r0]) + (F[n][3][r0+dE[n]] - F[n][3][r0]) - (Fv[n][3][r0+dE[n]] - Fv[n][3][r0]));

     calc_komega(n, r0, RHSt);

     RHS4 = - 2.0e-6 * ((TurbE[n][0][r0+dG[n]] - TurbE[n][0][r0]) - (TurbEv[n][0][r0+dG[n]] - TurbEv[n][0][r0]) + (TurbF[n][0][r0+dE[n]] - TurbF[n][0][r0]) - (TurbFv[n][0][r0+dE[n]] - TurbFv[n][0][r0]) - RHSt[0]);
     RHS5 = - 2.0e-6 * ((TurbE[n][1][r0+dG[n]] - TurbE[n][1][r0]) - (TurbEv[n][1][r0+dG[n]] - TurbEv[n][1][r0]) + (TurbF[n][1][r0+dE[n]] - TurbF[n][1][r0]) - (TurbFv[n][1][r0+dE[n]] - TurbFv[n][1][r0]) - RHSt[1]);



     if(t==0){
       tmpEE[n][0][r0] = RHS0;
       tmpEE[n][1][r0] = RHS1;
       tmpEE[n][2][r0] = RHS2;
       tmpEE[n][3][r0] = RHS3;
       TurbtmpEE[n][0][r0] = RHS4;
       TurbtmpEE[n][1][r0] = RHS5;
     }

     rhsF[n][0][r0] = (tmpQ[n][0][r0] - Q[n][0][r0]) + 0.5 * (RHS0 + tmpEE[n][0][r0]);
     rhsF[n][1][r0] = (tmpQ[n][1][r0] - Q[n][1][r0]) + 0.5 * (RHS1 + tmpEE[n][1][r0]);
     rhsF[n][2][r0] = (tmpQ[n][2][r0] - Q[n][2][r0]) + 0.5 * (RHS2 + tmpEE[n][2][r0]);
     rhsF[n][3][r0] = (tmpQ[n][3][r0] - Q[n][3][r0]) + 0.5 * (RHS3 + tmpEE[n][3][r0]);
     rhsTurbF[n][0][r0] = (TurbtmpQ[n][0][r0] - TurbQ[n][0][r0]) + 0.5 * (RHS4 + TurbtmpEE[n][0][r0]);
     rhsTurbF[n][1][r0] = (TurbtmpQ[n][1][r0] - TurbQ[n][1][r0]) + 0.5 * (RHS5 + TurbtmpEE[n][1][r0]);

   }
 }
      }
    }

    for(t=0;t<4;t++){
      for(n=0;n<3;n++){
 int i, j, r0;






#pragma omp for private(i, j, r0)
   for(j=2;j<jt[n]-3;j++){
     for(i=2;i<it[n]-3;i++){
       double Jaco, invQ;
       double RHS0, RHS1, RHS2, RHS3;
       double spe_r0[2];
       double spe_rt[2];
       double deltaFlux[2][6];
       double rhs1[6];
       double LDinv;
       int XI = 0;
       int ETA = 1;

       r0 = dim[n](i, j);

       calcPM(r0,n,-1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_r0);

       rhs1[0] = rhsF[n][0][r0] + 2.0e-6 * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
       rhs1[1] = rhsF[n][1][r0] + 2.0e-6 * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
       rhs1[2] = rhsF[n][2][r0] + 2.0e-6 * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
       rhs1[3] = rhsF[n][3][r0] + 2.0e-6 * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
       rhs1[4] = rhsTurbF[n][0][r0] + 2.0e-6 * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
       rhs1[5] = rhsTurbF[n][1][r0] + 2.0e-6 * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

       calcPM(r0,n,1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_rt);

       rhs1[0] -= 2.0e-6 * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
       rhs1[1] -= 2.0e-6 * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
       rhs1[2] -= 2.0e-6 * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
       rhs1[3] -= 2.0e-6 * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
       rhs1[4] -= 2.0e-6 * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
       rhs1[5] -= 2.0e-6 * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

       LDinv = 1.0 / (1.0+0.5*2.0e-6*(spe_r0[0]+spe_r0[1]+spe_rt[0]+spe_rt[1]));

       dQ[n][0][r0] = rhs1[0] * LDinv;
       dQ[n][1][r0] = rhs1[1] * LDinv;
       dQ[n][2][r0] = rhs1[2] * LDinv;
       dQ[n][3][r0] = rhs1[3] * LDinv;
       TurbdQ[n][0][r0] = rhs1[4] * LDinv;
       TurbdQ[n][1][r0] = rhs1[5] * LDinv;
     }
   }

#pragma omp for private(i, j, r0)
   for(j=jt[n]-4;j>1;j--){
     for(i=it[n]-4;i>1;i--){
       double Jaco, invQ;
       double RHS0, RHS1, RHS2, RHS3;
       double spe_r0[2];
       double spe_rt[2];
       double deltaFlux[2][6];
       double rhs1[6];
       double LDinv;
       int XI = 0;
       int ETA = 1;

       r0 = dim[n](i, j);

       calcPM(r0,n,-1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_r0);

       rhs1[0] = rhsF[n][0][r0] + 2.0e-6 * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
       rhs1[1] = rhsF[n][1][r0] + 2.0e-6 * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
       rhs1[2] = rhsF[n][2][r0] + 2.0e-6 * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
       rhs1[3] = rhsF[n][3][r0] + 2.0e-6 * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
       rhs1[4] = rhsTurbF[n][0][r0] + 2.0e-6 * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
       rhs1[5] = rhsTurbF[n][1][r0] + 2.0e-6 * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

       calcPM(r0,n,1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_rt);

       rhs1[0] -= 2.0e-6 * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
       rhs1[1] -= 2.0e-6 * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
       rhs1[2] -= 2.0e-6 * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
       rhs1[3] -= 2.0e-6 * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
       rhs1[4] -= 2.0e-6 * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
       rhs1[5] -= 2.0e-6 * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

       LDinv = 1.0 / (1.0+0.5*2.0e-6*(spe_r0[0]+spe_r0[1]+spe_rt[0]+spe_rt[1]));

       dQ[n][0][r0] = rhs1[0] * LDinv;
       dQ[n][1][r0] = rhs1[1] * LDinv;
       dQ[n][2][r0] = rhs1[2] * LDinv;
       dQ[n][3][r0] = rhs1[3] * LDinv;
       TurbdQ[n][0][r0] = rhs1[4] * LDinv;
       TurbdQ[n][1][r0] = rhs1[5] * LDinv;
     }
   }



      }
    }



    for(n=0;n<3;n++){
      int i, j, r0;
# 322 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
#pragma omp for private(i, j, r0)
 for(j=2;j<jt[n]-3;j++){
   for(i=2;i<it[n]-3;i++){
     double Jaco, invQ;
     double RHS0, RHS1, RHS2, RHS3;
     double LDinv;
     double a1 = 0.31, omega_mut;

     r0 = dim[n](i, j);
     Jaco = 1.0 / S[n][r0];

     Q[n][0][r0] = Q[n][0][r0] + dQ[n][0][r0];
     Q[n][1][r0] = Q[n][1][r0] + dQ[n][1][r0];
     Q[n][2][r0] = Q[n][2][r0] + dQ[n][2][r0];
     Q[n][3][r0] = Q[n][3][r0] + dQ[n][3][r0];

     TurbQ[n][0][r0] = TurbQ[n][0][r0] + TurbdQ[n][0][r0];
     TurbQ[n][1][r0] = TurbQ[n][1][r0] + TurbdQ[n][1][r0];

     invQ = 1.0 / Q[n][0][r0];

     rho[n][r0] = Q[n][0][r0] * Jaco;
     ux[n][r0] = Q[n][1][r0] * invQ;
     uy[n][r0] = Q[n][2][r0] * invQ;
     e[n][r0] = Q[n][3][r0] * Jaco;

     p[n][r0] = Cons_calcP(n, r0);

     k_turb[n][r0] = TurbQ[n][0][r0] * invQ;

     if(k_turb[n][r0] < 1.0e-10){
       k_turb[n][r0] = 1.0e-10;
     }

     omega[n][r0] = TurbQ[n][1][r0] * invQ;
     omega_mut = max2f(a1 * omega[n][r0], calc_W(n, r0) * calc_F2(n, r0));
     Mut[n][r0] = a1 * rho[n][r0] * k_turb[n][r0] / omega_mut;

     error4 = dQ[n][3][r0] / Q[n][3][r0];

     if(errormax < fabs(error4)){
       errormax = fabs(error4);
       ii = i;
       jj = j;
       nn = n;
     }


     if(
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), double), __isnan((double)(
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), float), __isnanf((float)(
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), long double), __isnanl((long double)(
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       rho[n][r0]
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), (__builtin_trap(),(int)0))))
# 370 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                        ){
       printf("rho is nan! at (%d %d)\n",i,j);
       exit(1);
     }
     if(
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), double), __isnan((double)(
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), float), __isnanf((float)(
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), long double), __isnanl((long double)(
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       ux[n][r0]
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), (__builtin_trap(),(int)0))))
# 374 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                       ){
       printf("ux is nan! at (%d %d)\n",i,j);
       exit(1);
     }
     if(
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), double), __isnan((double)(
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), float), __isnanf((float)(
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), long double), __isnanl((long double)(
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       uy[n][r0]
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), (__builtin_trap(),(int)0))))
# 378 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                       ){
       printf("uy is nan! at (%d %d)\n",i,j);
       exit(1);
     }
     if(
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), double), __isnan((double)(
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), float), __isnanf((float)(
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       ), long double), __isnanl((long double)(
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
       e[n][r0]
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
       )), (__builtin_trap(),(int)0))))
# 382 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                      ){
       printf("e is nan! at (%d %d)\n",i,j);
       exit(1);
     }
       if(
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), double), __isnan((double)(
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), float), __isnanf((float)(
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), long double), __isnanl((long double)(
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         k_turb[n][r0]
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), (__builtin_trap(),(int)0))))
# 386 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                             ){ printf("k is nan! n=%d %d %d %e %e %e %e %d\n",time,i,j,k_turb[n][r0],omega[n][r0],Mut[n][r0],rho[n][r0],itr); exit(1);}
       if(
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), double), __isnan((double)(
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), float), __isnanf((float)(
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), __builtin_choose_expr ( __builtin_types_compatible_p (__typeof__ (
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         ), long double), __isnanl((long double)(
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
         omega[n][r0]
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h" 3
         )), (__builtin_trap(),(int)0))))
# 387 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\MFGS-SST.h"
                            ){ printf("omega is nan! n=%d %d %d %e %e %e %e %d\n",time,i,j,k_turb[n][r0],omega[n][r0],Mut[n][r0],rho[n][r0],itr); exit(1);}


   }
 }



    }

    boundary();

    if(itr==0){
      printf("time:%d n:%d i:%d j:%d errormax:%e itr:%d\n",time,nn,ii,jj,errormax,itr);
    }

  }
}
# 38 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c" 2
# 58 "C:\\Users\\Uindmill\\Desktop\\Laboratory-kadai\\円柱周りのNS方程式\\encyu_2D_source\\encyu_2D_source\\main.c"
int main(){
  int time, r0, i, j;
  int cont = 0;

  read();

  Initial();

  PostFlow_input(cont);


  komega_ini();






  boundary();

  time=cont;


  while(1){
    Cons_tmp();

    gauss_seidel(time);

    time++;


    if(time%2000==0){
      PostFlow_output(time);
    }

  }

  return 0;

}
