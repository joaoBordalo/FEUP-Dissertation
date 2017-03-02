# FEUP-Dissertation
for PDIS and  Master Degree Dissertation


[Work Plan](https://docs.google.com/document/d/1EaRwrBXzREETSml68tNRoZJT4m01oLyG0Dr0M8CWDNk/edit)
[Proposal](https://docs.google.com/document/d/10GmOw57nbpL4KeOVmFNBExa8AKJa6nUK6WsU4PIATa0/edit)
[Abstract](
)
[Presentaton]()



# Dissertation description

**Enquadramento do trabalho:**	As plataformas computacionais são hoje em dia heterogéneas, contendo um processador central e um ou mais elementos aceleradores. Estes elementos de processamento têm características diferentes, sendo cada um deles adequado, ou seja obtêm melhor desempenho, para um determinado tipo de operação. Por outro lado as aplicações são compostas por diversos tipos de operações que poderão ser melhor executadas considerando os vários elementos de processamento disponíveis. 
Neste trabalho pretende-se desenvolver estratégias de execução de aplicações em sistemas heterogéneos e desenvolver mecanismos que possibilitem a configuração automática em função da plataforma disponível.

Este trabalho enquadra-se no projeto ANTAREX (www-antarex-project.eu). 
Objetivos e resultados esperados:	Desenvolver estratégias de configuração automática para aplicações de modo a otimizar a sua execução em plataformas heterogéneas, restritas a uma deadline e custo energético.


**Aspetos inovadores:**	Adaptação da execução de aplicações minimizando os custos energéticos e garantindo as restrições para o tempo de processamento.


**Plano de trabalho provisório:**	
1. Estudar as plataformas heterogéneas disponíveis. 
2. Monitorização dos elementos de processamento em termos de energia e capacidade de processamento. 
3. Estudar e desenvolver estratégias de autotuning para as aplicações alvo. 
4. Implementar e validar as estratégias propostas. 
5. Escrita da dissertação. 


**Referências bibiográficas:**	

*Kaushik Datta. Stencil computation optimization and auto-tuning on state-of-the-art multicore architectures. Proceeding SC '08 Proceedings of the 2008 ACM/IEEE conference on Supercomputing 

*Davide Gadioli, Gianluca Palermo, Cristina Silvano, "Application Autotuning to Support Runtime Adaptivity in Multicore Architectures", Proceeding of XV International Conference on Systems, Architectures, Modeling, and Simulation, IC-SAMOS 2015 

betweenness
g++ *.cpp -fopenmp -std=gnu++11 -o test.out
./teste.out


# Kremlin Fix

When installing Kremlin, executing make in cmd at kremlin directory an error occured at 30% of Kremlin istalation:

[ 30%] Building CXX object lib/Transforms/KremlinInstrument/CMakeFiles/KremlinInstrument.dir/KremlibDump.cpp.o
In file included from /usr/include/fcntl.h:279:0,
                 from /home/joaobordalo/Desktop/antarex/kremlin/instrument/llvm/llvm-3.6.1.src/lib/Transforms/KremlinInstrument/KremlibDump.cpp:11:
In function ‘int open(const char*, int, ...)’,
    inlined from ‘virtual bool {anonymous}::KremlibDump::runOnModule(llvm::Module&)’ at /home/joaobordalo/Desktop/antarex/kremlin/instrument/llvm/llvm-3.6.1.src/lib/Transforms/KremlinInstrument/KremlibDump.cpp:231:62:
/usr/include/x86_64-linux-gnu/bits/fcntl2.h:50:26: error: call to ‘__open_missing_mode’ declared with attribute error: open with O_CREAT in second argument needs 3 arguments
    __open_missing_mode ();
                          ^

The work around is:
- add  #include <unistd.h>

- in function  virtual bool runOnModule(Module &M):

before: 
virtual bool runOnModule(Module &M) {
            LLVMTypes types(M.getContext());

            std::string dump_filename = M.getModuleIdentifier();
            dump_filename = dump_filename.substr(0,dump_filename.find_first_of("."));
            dump_filename.append(".kdump");

            log.debug() << "Writing kremlib calls to " << dump_filename << "\n";

            int dump_fd = open(dump_filename.c_str(), O_RDWR | O_CREAT);
            if (dump_fd == -1) {
                LOG_FATAL() << "Could not open file: " << dump_filename << "\n";
                LOG_FATAL() << "\t Reason: " << strerror(errno) << "\n";
                return false;
            }

            // @note dump_fd is automatically closed when dum_raw_os is destroyed
            raw_fd_ostream* dump_raw_os = new raw_fd_ostream(dump_fd, true, false);

            std::set<std::string> kremlib_calls;
            addKremlibCallsToSet(kremlib_calls);

            // Now we'll look for calls to logRegionEntry/Exit and replace old region ID with mapped value
            for(Module::iterator func = M.begin(), f_e = M.end(); func != f_e; ++func) {
                processFunction(func,kremlib_calls, *dump_raw_os);
            }

            //dump_file.close();
            delete dump_raw_os;

            return false;
        }// end runOnModule(...)

        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesCFG();
        }

   after: (see bold to check what was added)
virtual bool runOnModule(Module &M) {
            LLVMTypes types(M.getContext());

            std::string dump_filename = M.getModuleIdentifier();
            dump_filename = dump_filename.substr(0,dump_filename.find_first_of("."));
            dump_filename.append(".kdump");

            log.debug() << "Writing kremlib calls to " << dump_filename << "\n";

            int dump_fd = open(dump_filename.c_str(), O_RDWR | O_CREAT, **S_IWUSR**);
            if (dump_fd == -1) {
                LOG_FATAL() << "Could not open file: " << dump_filename << "\n";
                LOG_FATAL() << "\t Reason: " << strerror(errno) << "\n";
                return false;
            }

            // @note dump_fd is automatically closed when dum_raw_os is destroyed
            raw_fd_ostream* dump_raw_os = new raw_fd_ostream(dump_fd, true, false);

            std::set<std::string> kremlib_calls;
            addKremlibCallsToSet(kremlib_calls);

            // Now we'll look for calls to logRegionEntry/Exit and replace old region ID with mapped value
            for(Module::iterator func = M.begin(), f_e = M.end(); func != f_e; ++func) {
                processFunction(func,kremlib_calls, *dump_raw_os);
            }

            //dump_file.close();
            delete dump_raw_os;

            return false;
        }// end runOnModule(...)

        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesCFG();
        }
