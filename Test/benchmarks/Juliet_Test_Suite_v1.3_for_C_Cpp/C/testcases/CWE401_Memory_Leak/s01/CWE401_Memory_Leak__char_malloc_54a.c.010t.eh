
;; Function CWE401_Memory_Leak__char_malloc_54_bad (CWE401_Memory_Leak__char_malloc_54_bad, funcdef_no=82, decl_uid=4331, cgraph_uid=82, symbol_order=82)

CWE401_Memory_Leak__char_malloc_54_bad ()
{
  char * data;

  data = 0B;
  data = malloc (100);
  if (data == 0B) goto <D.4347>; else goto <D.4348>;
  <D.4347>:
  exit (-1);
  <D.4348>:
  strcpy (data, "A String");
  printLine (data);
  CWE401_Memory_Leak__char_malloc_54b_badSink (data);
  return;
}



;; Function strcpy (<unset-asm-name>, funcdef_no=45, decl_uid=750, cgraph_uid=45, symbol_order=45)

__attribute__((__artificial__, __gnu_inline__, __always_inline__, __nothrow__, __leaf__))
strcpy (char * restrict __dest, const char * restrict __src)
{
  char * D.4349;

  _1 = __builtin_object_size (__dest, 1);
  D.4349 = __builtin___strcpy_chk (__dest, __src, _1);
  goto <D.4350>;
  <D.4350>:
  return D.4349;
}



;; Function CWE401_Memory_Leak__char_malloc_54_good (CWE401_Memory_Leak__char_malloc_54_good, funcdef_no=85, decl_uid=4344, cgraph_uid=85, symbol_order=85)

CWE401_Memory_Leak__char_malloc_54_good ()
{
  goodG2B ();
  goodB2G ();
  return;
}



;; Function goodG2B (goodG2B, funcdef_no=83, decl_uid=4336, cgraph_uid=83, symbol_order=83)

goodG2B ()
{
  char * data;

  data = 0B;
  data = __builtin_alloca (100);
  strcpy (data, "A String");
  printLine (data);
  CWE401_Memory_Leak__char_malloc_54b_goodG2BSink (data);
  return;
}



;; Function goodB2G (goodB2G, funcdef_no=84, decl_uid=4341, cgraph_uid=84, symbol_order=84)

goodB2G ()
{
  char * data;

  data = 0B;
  data = malloc (100);
  if (data == 0B) goto <D.4351>; else goto <D.4352>;
  <D.4351>:
  exit (-1);
  <D.4352>:
  strcpy (data, "A String");
  printLine (data);
  CWE401_Memory_Leak__char_malloc_54b_goodB2GSink (data);
  return;
}


