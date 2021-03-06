/* libunwind - a platform-independent unwind library

   Copied from src/x86_64/, modified slightly (or made empty stubs) for
   building frysk successfully on ppc64, by Wu Zhou <woodzltc@cn.ibm.com>

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#include <libunwind_i.h>

#ifdef UNW_TARGET_PPC64
#include "../ppc64/init.h"
#else
#include "../ppc32/init.h"
#endif

#ifdef UNW_REMOTE_ONLY

PROTECTED int
unw_init_local (unw_cursor_t *cursor, ucontext_t *uc)
{
  /* XXX: empty stub.  */
  return -UNW_EINVAL;
}

#else /* !UNW_REMOTE_ONLY */

PROTECTED int
unw_init_local (unw_cursor_t *cursor, ucontext_t *uc)
{
  struct cursor *c = (struct cursor *) cursor;

  if (tdep_needs_initialization)
    tdep_init ();

  Debug (1, "(cursor=%p)\n", c);

  c->dwarf.as = unw_local_addr_space;
  c->dwarf.as_arg = uc;
  #ifdef UNW_TARGET_PPC64
    return common_init_ppc64 (c);
  #else
    return common_init_ppc32 (c);
  #endif
}

#endif /* !UNW_REMOTE_ONLY */
