%%%
%%% Authors:
%%%   Denys Duchier (duchier@ps.uni-sb.de)
%%%
%%% Contributor:
%%%   Christian Schulte, 1998
%%%
%%% Copyright:
%%%   Denys Duchier, 1997
%%%
%%% Last change:
%%%   $Date$ by $Author$
%%%   $Revision$
%%%
%%% This file is part of Mozart, an implementation
%%% of Oz 3
%%%    $MOZARTURL$
%%%
%%% See the file "LICENSE" or
%%%    $LICENSEURL$
%%% for information on usage and redistribution
%%% of this file, and for a DISCLAIMER OF ALL
%%% WARRANTIES.
%%%

functor $ prop once

import
   Finalize from 'x-oz-boot:Finalize'

export
   register:   Register
   setHandler: SetHandler

body

   Register   = Finalize.register
   SetHandler = Finalize.setHandler

   local
      proc {FinalizeEntry Value|Handler}
         {Handler Value}
      end
      proc {FinalizeHandler L}
         {ForAll L FinalizeEntry}
      end
   in
      {SetHandler FinalizeHandler}
   end
end
