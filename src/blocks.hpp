#ifndef HEADER_BLOCKS
#define HEADER_BLOCKS

class BaseBlock{};
class CaseBlock     : BaseBlock{};
class CatchBlock    : BaseBlock{};
class DefaultBlock  : BaseBlock{};
class DoBlock       : BaseBlock{};
class ElseBlock     : BaseBlock{};
class FinallyBlock  : BaseBlock{};
class ForBlock      : BaseBlock{};
class IfBlock       : BaseBlock{};
class ObjectBlock   : BaseBlock{};
class SwitchBlock   : BaseBlock{};
class TryBlock      : BaseBlock{};
class WhileBlock    : BaseBlock{};
class WithBlock     : BaseBlock{};

class BaseScope     : BaseBlock{};
class GlobalScope   : BaseScope{};
class FunctionScope : BaseScope{};

#endif
