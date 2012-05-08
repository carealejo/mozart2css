// Copyright © 2011, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __COREINTERFACES_DECL_H
#define __COREINTERFACES_DECL_H

#include "mozartcore-decl.hh"

#include "coredatatypes-decl.hh"
#include "exchelpers-decl.hh"

namespace mozart {

class DataflowVariable;
template<>
struct Interface<DataflowVariable>: ImplementedBy<Unbound, Variable>, NoAutoWait {
  void addToSuspendList(RichNode self, VM vm, Runnable* thread) {
  }

  void addToSuspendList(RichNode self, VM vm, RichNode variable) {
  }

  /**
   * Precondition:
   *   self.type()->getStructuralBehavior() == sbVariable
   */
  Space* home(RichNode self) {
    assert(self.type()->getStructuralBehavior() == sbVariable);
    assert(false);
    return nullptr;
  }

  /**
   * Precondition:
   *   self.type()->getStructuralBehavior() == sbVariable
   */
  OpResult bind(RichNode self, VM vm, RichNode src) {
    assert(self.type()->getStructuralBehavior() == sbVariable);
    assert(false);
    return raiseTypeError(vm, u"Variable", self);
  }
};

class ValueEquatable;
template<>
struct Interface<ValueEquatable>:
  ImplementedBy<SmallInt, Atom, Boolean, Float> {

  /**
   * Precondition:
   *   self.type()->getStructuralBehavior() == sbValue
   *   self.type() == right.type()
   */
  bool equals(RichNode self, VM vm, RichNode right) {
    assert(self.type()->getStructuralBehavior() == sbValue);
    assert(self.type() == right.type());
    assert(false);
    return false;
  }
};

class StructuralEquatable;
template<>
struct Interface<StructuralEquatable>:
  ImplementedBy<Tuple, Cons, Record, Arity> {

  /**
   * Precondition:
   *   self.type()->getStructuralBehavior() == sbStructural
   *   self.type() == right.type()
   */
  bool equals(RichNode self, VM vm, RichNode right, WalkStack& stack) {
    assert(self.type()->getStructuralBehavior() == sbStructural);
    assert(self.type() == right.type());
    assert(false);
    return false;
  }
};

class BuiltinCallable;
template<>
struct Interface<BuiltinCallable>: ImplementedBy<BuiltinProcedure> {
  OpResult callBuiltin(RichNode self, VM vm, int argc,
                       UnstableNode* args[]) {
    return raiseTypeError(vm, u"BuiltinProcedure", self);
  }

  template <class... Args>
  OpResult callBuiltin(RichNode self, VM vm, Args&&... args) {
    return raiseTypeError(vm, u"BuiltinProcedure", self);
  }
};

class Callable;
template<>
struct Interface<Callable>: ImplementedBy<Abstraction, BuiltinProcedure> {
  OpResult getCallInfo(RichNode self, VM vm, int& arity, StableNode*& body,
                       ProgramCounter& start, int& Xcount,
                       StaticArray<StableNode>& Gs,
                       StaticArray<StableNode>& Ks) {
    arity = 0;
    body = nullptr;
    start = nullptr;
    Xcount = 0;
    Gs = nullptr;
    Ks = nullptr;
    return raiseTypeError(vm, u"Abstraction", self);
  }
};

class CodeAreaProvider;
template<>
struct Interface<CodeAreaProvider>: ImplementedBy<CodeArea> {
  OpResult getCodeAreaInfo(RichNode self, VM vm, ProgramCounter& start,
                           int& Xcount, StaticArray<StableNode>& Ks) {
    start = nullptr;
    Xcount = 0;
    Ks = nullptr;
    return raiseTypeError(vm, u"CodeArea", self);
  }
};

class Numeric;
template<>
struct Interface<Numeric>: ImplementedBy<SmallInt, Float> {
  OpResult add(RichNode self, VM vm,
               RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }

  OpResult subtract(RichNode self, VM vm,
                    RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }

  OpResult multiply(RichNode self, VM vm,
                    RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }

  OpResult divide(RichNode self, VM vm,
                  RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }

  OpResult div(RichNode self, VM vm,
               RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }

  OpResult mod(RichNode self, VM vm,
               RichNode right, UnstableNode& result) {
    return raiseTypeError(vm, u"Numeric", self);
  }
};

class IntegerValue;
template<>
struct Interface<IntegerValue>: ImplementedBy<SmallInt> {
  OpResult intValue(RichNode self, VM vm, nativeint& result) {
    return raiseTypeError(vm, u"Integer", self);
  }

  OpResult equalsInteger(RichNode self, VM vm,
                         nativeint right, bool& result) {
    result = false;
    return OpResult::proceed();
  }

  OpResult addValue(RichNode self, VM vm,
                    nativeint b, UnstableNode& result) {
    return raiseTypeError(vm, u"Integer", self);
  }
};

class FloatValue;
template<>
struct Interface<FloatValue>: ImplementedBy<Float> {
  OpResult floatValue(RichNode self, VM vm, double& result) {
    return raiseTypeError(vm, u"Float", self);
  }

  OpResult equalsFloat(RichNode self, VM vm,
                       double right, bool& result) {
    result = false;
    return OpResult::proceed();
  }

  OpResult addValue(RichNode self, VM vm,
                    double b, UnstableNode& result) {
    return raiseTypeError(vm, u"Float", self);
  }
};

class BooleanValue;
template<>
struct Interface<BooleanValue>: ImplementedBy<Boolean> {
  OpResult boolValue(RichNode self, VM vm, bool& result) {
    return raiseTypeError(vm, u"Boolean", self);
  }

  OpResult valueOrNotBool(RichNode self, VM vm, BoolOrNotBool& result) {
    result = bNotBool;
    return OpResult::proceed();
  }
};

class RecordLike;
template<>
struct Interface<RecordLike>: ImplementedBy<Tuple, Record, Cons, Atom> {
  OpResult label(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Record", self);
  }

  OpResult width(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Record", self);
  }

  OpResult dot(RichNode self, VM vm, RichNode feature,
               UnstableNode& result) {
    return raiseTypeError(vm, u"Record", self);
  }

  OpResult dotNumber(RichNode self, VM vm, nativeint feature,
                     UnstableNode& result) {
    return raiseTypeError(vm, u"Record", self);
  }

  OpResult waitOr(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Record", self);
  }
};

class ArrayInitializer;
template<>
struct Interface<ArrayInitializer>:
  ImplementedBy<Tuple, Record, Abstraction, CodeArea> {

  OpResult initElement(RichNode self, VM vm, size_t index, RichNode value) {
    return raiseTypeError(vm, u"Array initializer", self);
  }
};

class SpaceLike;
template<>
struct Interface<SpaceLike>: ImplementedBy<ReifiedSpace, DeletedSpace> {
  OpResult askSpace(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Space", self);
  }

  OpResult askVerboseSpace(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Space", self);
  }

  OpResult mergeSpace(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Space", self);
  }

  OpResult commitSpace(RichNode self, VM vm, RichNode value) {
    return raiseTypeError(vm, u"Space", self);
  }

  OpResult cloneSpace(RichNode self, VM vm, UnstableNode& result) {
    return raiseTypeError(vm, u"Space", self);
  }
};

}

#endif // __COREINTERFACES_DECL_H
