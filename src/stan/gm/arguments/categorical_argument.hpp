#ifndef __STAN__GM__ARGUMENTS__CATEGORY__ARGUMENT__BETA__
#define __STAN__GM__ARGUMENTS__CATEGORY__ARGUMENT__BETA__

#include <vector>
#include <stan/gm/arguments/argument.hpp>

namespace stan {
  
  namespace gm {
    
    class categorical_argument: public argument {
      
    public:
      
      virtual ~categorical_argument() {
        
        for (std::vector<argument*>::iterator it = _subarguments.begin();
             it != _subarguments.end(); ++it) {
          delete *it;
        }
        
        _subarguments.clear();
        
      }
      
      void print(std::ostream* s, int depth, const char prefix) {
        if(!s) return;
        std::string indent(compute_indent(depth), ' ');
        *s << prefix << indent << _name << std::endl;
        
        for (std::vector<argument*>::iterator it = _subarguments.begin();
             it != _subarguments.end(); ++it)
          (*it)->print(s, depth + 1, prefix);
      }
      
      void print_help(std::ostream* s, int depth, bool recurse) {
        
        if(!s) return;
        
        std::string indent(indent_width * depth, ' ');
        std::string subindent(indent_width, ' ');
        
        *s << indent << _name << std::endl;
        *s << indent << subindent << _description << std::endl;
        *s << indent << subindent << "Valid subarguments:";
        
        for (std::vector<argument*>::iterator it = _subarguments.begin();
             it != _subarguments.end(); ++it)
          *s << " " << (*it)->name();
        *s << std::endl << std::endl;
        
        if (recurse) {
          for (std::vector<argument*>::iterator it = _subarguments.begin();
               it != _subarguments.end(); ++it)
            (*it)->print_help(s, depth + 1, true);
        }
        
      }
      
      bool parse_args(std::vector<std::string>& args, std::ostream* out,
                      std::ostream* err, bool& help_flag) {
        
        bool good_arg = true;
        bool valid_arg = true;
        
        while(good_arg) {
          
          if(args.size() == 0) return valid_arg;
          
          good_arg = false;
          
          std::string cat_name = args.back();
          
          if (cat_name == "help") {
            print_help(out, 0, false);
            help_flag |= true;
            args.clear();
            return true;
          }
          else if(cat_name == "help-all") {
            print_help(out, 0, true);
            help_flag |= true;
            args.clear();
            return true;
          }
          
          std::string val_name;
          std::string val;
          split_arg(cat_name, val_name, val);
          
          for (std::vector<argument*>::iterator it = _subarguments.begin();
               it != _subarguments.end(); ++it) {
            
            if( (*it)->name() == cat_name) {
              args.pop_back();
              valid_arg &= (*it)->parse_args(args, out, err, help_flag);
              good_arg = true;
            }
            else if( (*it)->name() == val_name ) {
              valid_arg &= (*it)->parse_args(args, out, err, help_flag);
              good_arg = true;
            }
            
          }
          
        }
        
        return valid_arg;
        
      };
      
      argument* arg(std::string name) {
        
        for (std::vector<argument*>::iterator it = _subarguments.begin();
             it != _subarguments.end(); ++it)
          if( name == (*it)->name() ) return (*it);
        
        return 0;
        
      }
      
    protected:
      
      std::vector<argument*> _subarguments;
      
    };
    
  } // gm
  
} // stan

#endif