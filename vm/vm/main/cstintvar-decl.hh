#ifndef __CSTINTVAR_DECL_H
#define __CSTINTVAR_DECL_H

#include "mozartcore-decl.hh"

namespace mozart {

class CstIntVar;

#ifndef MOZART_GENERATOR
#include "CstIntVar-implem-decl.hh"
#endif  
  
class CstIntVar: public WithHome,
  public DataType<CstIntVar>,
  public Transient,
  public WithVariableBehavior<5> {
public:
  //typedef SelfType<CstIntVar>::Self Self;

  // TODO: uuid is missing

  // TODO: getTypeAtomg is missing

  CstIntVar(VM vm, size_t index)
    : WithHome(vm), _varIndex(index) {}

  // Constructor from min and max elements in the domain
  inline
  CstIntVar(VM vm, RichNode min, RichNode max);

  // Constructor from a list (?) describing the domain
  CstIntVar(VM vm, RichNode domain)
    : WithHome(vm), _varIndex(0) {
      // TODO
      assert(false);
  }

  // TODO: Ask Sebastien about this constructor. The docs says that is needed
  // if yes, what is its semantics?
  // CstIntVar(VM vm, SpaceRef home)
  //   : WithHome(home), _varIndex(0) {}

  CstIntVar(VM vm, GR gr, CstIntVar from)
    //    : WithHome(vm,gr,from->home()), _varIndex(from->_varIndex) {}
    : WithHome(vm,gr,from), _varIndex(from._varIndex) {}

  inline
  static bool validAsElement(nativeint x);

public:
  Gecode::IntVar& getVar(void) {
    return home()->getCstSpace().intVar(_varIndex);
  }
public:
  // IntVarLike interface
  bool isIntVarLike(VM vm) {
    return true;
  }

  Gecode::IntVar& intVar(VM vm) {
    return getVar();
  }

  inline
  UnstableNode min(VM vm);

  inline
  UnstableNode max(VM vm);

  inline
  UnstableNode value(VM vm);

  inline
  UnstableNode isIn(VM vm, RichNode right);
public:
  // ConstraintVar interface
  inline
  bool assigned(VM vm) {
    return getVar().assigned();
  }
public:
  // Miscellaneous
  void printReprToStream(RichNode self, VM vm, std::ostream& out, int depth, int width) {
    out << getVar();
  }
private:
  // The actual representation of a constraint integer variable is a 
  // Gecode::IntVar, here we store the index of an object of that class
  // inside an array stored by a Gecode::Space
  size_t _varIndex;
};// End class CstIntVar


///////////////////////
// Distributor_fd    //
///////////////////////

  template <class Strategy, class Value>
  class Distributor_fd: public Distributor {
  public:
    Distributor_fd(VM vm, Space* space, std::vector< Gecode::IntVar > v) {
      _vector = v;
      for(unsigned int i=0;i<_vector.size();i++){
	Gecode::IntVar var=_vector[i];
	unsigned int n=var.size();
	std::cout << var << "dominio " << n << std::endl;
	//if(n==1){
	//_vector.erase[i];
	//}
      }
      _var = OptVar::build(vm, space);
    }

    Distributor_fd(GR gr, Distributor_fd& from) {
      //_alternatives = from._alternatives;
      gr->copyUnstableNode(_var, from._var);
    }
    
    UnstableNode* getVar() {
      return &_var;
    }
    
    nativeint getAlternatives() {
      return _alternatives;
    }
    
    nativeint commit(VM vm, Space* space, nativeint value) {
      // if (value > _alternatives)
      //   return -value;
      
      // UnstableNode valueNode = build(vm, value);
      // new (vm) UnifyThread(vm, space, &_var, &valueNode);
      std::cout << "Commit distributor_fd" << std::endl;
      
      return 0;
    }
    
    virtual Distributor* replicate(GR gr) {
      return new (gr->vm) Distributor_fd(gr, *this);
    }
    
  private:
    Strategy _s;
    Value _v;
    nativeint _alternatives;
    std::vector< Gecode::IntVar > _vector;
    UnstableNode _var;
  };
  
#ifndef MOZART_GENERATOR
#include "CstIntVar-implem-decl-after.hh"
#endif
  
} // End namespace mozart

#endif // __CSTINTVAR_DECL_H
