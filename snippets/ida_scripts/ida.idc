//
//      This file is automatically executed when IDA is started.
//      You can define your own IDC functions and assign hotkeys to them.
//
//      You may add your frequently used functions here and they will
//      be always available.
//
//
#include <idc.idc>

//-----------------------------------------------------------------------
// A singleton class for managing breakpoints
class BreakpointManager
{
  // Return the breakpoint quantity
  Count()
  {
    return GetBptQty();
  }

  // Return a breakpoint object
  Get(index)
  {
    auto count = this.Count();
    if ( index >= count )
      throw form("Invalid breakpoint index %d (0..%d expected).", index, count);
    return Breakpoint(index);
  }

  // Add a breakpoint
  Add(bpt)
  {
    return bpt._add();
  }

  // Add a breakpoint to group
  AddToGroup(bpt, group_name)
  {
    return bpt._add(group_name);
  }

  // Delete a breakpoint
  Delete(bpt)
  {
    return bpt._delete();
  }

  // Update a breakpoint
  // Note: Location attributes cannot be updated, recreation of the
  //       breakpoint is required
  Update(bpt)
  {
    return bpt._update();
  }

  // Find a breakpoint using its location attributes and
  // returns a new breakpoint object or 0
  Find(bpt)
  {
    return bpt._find();
  }
}

// Breakpoint manager class instance
extern Breakpoints;

//-----------------------------------------------------------------------
// Get name of the current processor
static get_processor_name(void)
{
  auto i;

  auto procname = "";
  for ( i=0; i < 8; i++ )
  {
    auto chr = GetCharPrm(INF_PROCNAME+i);
    if ( chr == 0 )
      break;
    procname = procname + chr;
  }
  return procname;
}

//-----------------------------------------------------------------------
// Get signed extended 16-bit value
static SWord(ea)
{
  auto v = Word(ea);
  if ( v & 0x8000 )
    v = v | ~0xFFFF;
  return v;
}

//-----------------------------------------------------------------------
// Create a switch idiom for m68k
static py_68k_create_switch()
{
    auto path = "execfile('D:\\Tools\\ida_scripts\\create_switch.py')";
    Message(path + "\n");
    RunPythonStatement(path);
}

static hotkey_F4()
{
    auto path = "execfile('D:\\Tools\\ida_scripts\\hotkey_F4.py')";
    Message(path + "\n");
    RunPythonStatement(path);
}

static hotkey_F7()
{
    auto path = "execfile('D:\\Tools\\ida_scripts\\hotkey_F7.py')";
    Message(path + "\n");
    RunPythonStatement(path);
}

static hotkey_F8()
{
    auto path = "execfile('D:\\Tools\\ida_scripts\\hotkey_F8.py')";
    Message(path + "\n");
    RunPythonStatement(path);
}

static hotkey_Ctrl_F9()
{
    auto path = "execfile('D:\\Tools\\ida_scripts\\hotkey_Ctrl_F9.py')";
    Message(path + "\n");
    RunPythonStatement(path);
}

//-----------------------------------------------------------------------
static main(void)
{
  //
  //      This function is executed when IDA is started.
  //
  //      Add statements to fine-tune your IDA here.
  //

  // Instantiate the breakpoints singleton object
  Breakpoints = BreakpointManager();

  // uncomment this line to remove full paths in the debugger process options:
  // SetCharPrm(INF_LFLAGS, LFLG_DBG_NOPATH|GetCharPrm(INF_LFLAGS));
 
  AddHotkey("F4", "hotkey_F4");
  AddHotkey("F7", "hotkey_F7");
  AddHotkey("F8", "hotkey_F8");
  AddHotkey("Ctrl+F9", "hotkey_Ctrl_F9");
  AddHotkey("F9", "py_68k_create_switch");
}

