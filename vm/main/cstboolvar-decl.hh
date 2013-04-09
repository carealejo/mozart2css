#ifndef __CSTBOOLVAR_DECL_H
#define __CSTBOOLVAR_DECL_H

#include "mozartcore-decl.hh"

namespace mozart {

class CstBoolVar;

#ifndef MOZART_GENERATOR
#include "CstBoolVar-implem-decl.hh"
#endif

class CstBoolVar: public WithHome,
  public DataType<CstBoolVar>,
  public Transient,
  public WithVariableBehavior<5> {
public:
  CstBoolVar(VM vm, size_t index)
    : WithHome(vm), _varIndex(index) {}

  // Constructor from min and max elements in the domain
  inline
  CstBoolVar(VM vm);

  // TODO: Ask Sebastien about this constructor. The docs says that is needed
  // if yes, what is its semantics?
  // CstBoolVar(VM vm, SpaceRef home)
  //   : WithHome(home), _varIndex(0) {}

  CstBoolVar(VM vm, GR gr, CstBoolVar from)
    //    : WithHome(vm,gr,from->home()), _varIndex(from->_varIndex) {}
    : WithHome(vm,gr,from), _varIndex(from._varIndex) {}

public:
  Gecode::BoolVar& getVar(void) {
    return home()->getCstSpace().boolVar(_varIndex);
  }
public:
  // BoolVarLike interface
  bool isBoolVarLike(VM vm) {
    return true;
  }

  Gecode::BoolVar& boolVar(VM vm) {
    return getVar();
  }
public:
  // Miscellaneous
  void printReprToStream(RichNode self, VM vm, std::ostream& out, int depth, int width) {
    out << getVar();
  }
private:
  // The actual representation of a constraint integer variable is a 
  // Gecode::BoolVar, here we store the index of an object of that class
  // inside an array stored by a Gecode::Space
  size_t _varIndex;
};// End class CstBoolVar

#ifndef MOZART_GENERATOR
#include "CstBoolVar-implem-decl-after.hh"
#endif

} // End namespace mozart

#endif // __CSTBOOLVAR_DECL_H
