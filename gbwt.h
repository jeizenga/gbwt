/*
  Copyright (c) 2017 Genome Research Ltd.

  Author: Jouni Siren <jouni.siren@iki.fi>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef _GBWT_GBWT_H
#define _GBWT_GBWT_H

#include "files.h"
#include "support.h"

namespace gbwt
{

/*
  gbwt.h: Main GBWT structures.

  FIXME Reorganize: rename this file to dynamic_gbwt.h

  FIXME We currently assume that the alphabet is dense. In a multi-chromosome graph, the
  alphabet for an individual chromosome will be dense in range [a,b].
*/

//------------------------------------------------------------------------------

class DynamicGBWT
{
public:
  typedef DynamicRecord::size_type size_type;

//------------------------------------------------------------------------------

  DynamicGBWT();
  DynamicGBWT(const DynamicGBWT& source);
  DynamicGBWT(DynamicGBWT&& source);
  ~DynamicGBWT();

  void swap(DynamicGBWT& another);
  DynamicGBWT& operator=(const DynamicGBWT& source);
  DynamicGBWT& operator=(DynamicGBWT&& source);

  size_type serialize(std::ostream& out, sdsl::structure_tree_node* v = nullptr, std::string name = "") const;
  void load(std::istream& in);  // FIXME not tested

  const static std::string EXTENSION; // .gbwt

//------------------------------------------------------------------------------

  /*
    Insert one or more sequences to the GBWT. The text must be a concatenation of sequences,
    each of which ends with an endmarker (0). The new sequences receive identifiers starting
    from this->sequences().
  */
  void insert(const text_type& text);

//------------------------------------------------------------------------------

  inline size_type size() const { return this->header.size; }
  inline size_type sequences() const { return this->header.sequences; }
  inline size_type sigma() const { return this->header.alphabet_size; }
  inline size_type effective() const { return this->header.nodes; }
  inline size_type count(node_type node) const { return this->bwt[node].size(); }

//------------------------------------------------------------------------------

  size_type LF(node_type from, size_type i, node_type to) const;

//------------------------------------------------------------------------------

  GBWTHeader                 header;
  std::vector<DynamicRecord> bwt;

//------------------------------------------------------------------------------

private:
  void copy(const DynamicGBWT& source);

//------------------------------------------------------------------------------

}; // class DynamicGBWT

//------------------------------------------------------------------------------

} // namespace gbwt

#endif // _GBWT_GBWT_H
