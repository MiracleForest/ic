/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名 iCommand.hpp
 * @创建时间 2023.5.2.00:01
 * @创建者 ticks-tan
 * -----------------------------------------------------------------------------
 * 执行命令
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/

#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>

#ifdef __WINDOWS__
// todo Windows includes
#elif defined(__LINUX__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

SPACE(i)
{ 
	SPACE(core)
	{ 
		SPACE(process)
		{

#ifdef __LINUX__
                  // Command Result
                  class IAPI iCommandResult
                      : public basic::iBasic<iCommandResult>
                  {
                      using istring = data::text::istring;
                      iObject(iCommandResult);

                  public:
                      friend class iCommand;
                      ~iCommandResult() = default;
                      iCommandResult(CRef<iCommandResult>) = default;
                      Ref<iCommandResult> operator=(CRef<iCommandResult>) = default;
                      iCommandResult(RRef<iCommandResult>) noexcept = default;
                      Ref<iCommandResult> operator=(RRef<iCommandResult>) = default;

                      explicit operator bool() const { return _ret_code == 0; }

                  public:
                      // 标准输出
                      CRef<istring> output() const { return _output_buf; }
                      ulong output(Ptr<char> buf, ulong len, ulong start = 0) const {
                          ulong i = start;
                          for (; i < len && i < _output_buf.size(); ++i) {
                              buf[i] = _output_buf[i];
                          }
                          return i;
                      }
                      // 标准错误
                      CRef<istring> error() const { return _error_buf; }

                      ulong error(Ptr<char> buf, ulong len, ulong start) const {
                          ulong i = start;
                          for (; i < len && i < _output_buf.size(); ++i) {
                              buf[i] = _output_buf[i];
                          }
                          return i;
                      }

                    // 返回值
                    int retCode() const { return _ret_code; }

                  protected:
                      // 读取执行结果
                      void readToBuf();
                      // 初始化管道
                      void initPipe();
                      // 初始化父进程
                      void initInParent() const;
                      // 初始化子进程
                      void initInChild() const;
                      // 写入到子进程标准输入
                      void writeToInput(std::string &input) const;

                      explicit iCommandResult()
                          : _input_pipe{-1, -1}
                          , _output_pipe{-1, -1}
                          , _error_pipe{-1, -1} 
                      {  }

                      void closePipe() const 
                      {
                          if (_status > 1) {
                              ::close(_input_pipe[1]);
                              if (_status > 2) {
                                  ::close(_output_pipe[0]);
                                  if (_status > 3) {
                                      ::close(_error_pipe[0]);
                                  }
                              }
                          }
                      }

                  private:
                      int _ret_code{0};       // 返回值
                      int _status{0};         // 状态
                      int _input_pipe[2];     // 标准输入
                      int _output_pipe[2];    // 标准输出
                      int _error_pipe[2];     // 标准错误
                      istring _output_buf;    // 输出缓冲区
                      istring _error_buf;     // 错误缓冲区
                  }; // class Result


                  class iCommand final
                      : public basic::iBasic<iCommand>
                  {
                      using istring = data::text::istring;
                      iObject(iCommand);
                  public:
                      // 创建新Command
                      static iCommand New(Ref<istring> cmd) {
                          return std::move(iCommand{cmd});
                      }
                      static iCommand New(CPtr<char> cmd) {
                          return std::move(iCommand{cmd});
                      }

                      iCommand(CRef<iCommand>) = delete;
                      Ref<iCommand> operator=(CRef<iCommand>) = delete;

                      iCommand(RRef<iCommand>) noexcept = default;
                      Ref<iCommand> operator=(RRef<iCommand>) = default;

                      ~iCommand() = default;

                    public:
                      // 指定参数
                      Ref<iCommand> arg(Ref<istring> arg) {
                          if (!arg.empty()) {
                              _args.emplace_back(arg);
                          }
                          return *this;
                      }
                      Ref<iCommand> arg(CPtr<char> arg) {
                          if (arg != nullptr) {
                              _args.emplace_back(arg);
                          }
                          return *this;
                      }
                      Ref<iCommand> args(CRef<std::vector<istring>> args) {
                          for (auto &it : args) {
                              if (!it.empty()) {
                                  _args.emplace_back(it);
                              }
                          }
                          return *this;
                      }

                      // 指定环境变量
                      Ref<iCommand> env(Ref<istring> env) {
                          if (!env.empty()) {
                              _envs.emplace_back(env);
                          }
                          return *this;
                      }
                      Ref<iCommand> env(CPtr<char> env) {
                          if (env != nullptr) {
                              _envs.emplace_back(env);
                          }
                          return *this;
                      }

                      Ref<iCommand> envs(CRef<std::vector<istring>> envs) {
                          for (auto &it : envs) {
                              if (!envs.empty()) {
                                  _envs.emplace_back(it);
                              }
                          }
                          return *this;
                      }

                      // 指定输入
                      Ref<iCommand> input(CRef<istring> input) {
                          _input_buf += input;
                          return *this;
                      }
                      // ���һ������
                      Ref<iCommand> input(CRef<std::initializer_list<istring>> list) {
                          for (auto &it : list) {
                              _input_buf += it;
                          }
                          return *this;
                      }

                      // 同步执行，阻塞等待
                      Ref<iCommandResult> run();
                      // 异步执行，不阻塞
                      Ref<iCommand> start();
                      // 阻塞等待
                      Ref<iCommandResult> wait();

                    protected:
                      explicit iCommand(Ref<istring> cmd) 
                          : _command(cmd) 
                      {
                          _args.emplace_back(_command);
                      }
                      explicit iCommand(CPtr<char> cmd) 
                          : _command(cmd) 
                      {
                          _args.emplace_back(cmd);
                      }

                    private:
                      iCommandResult _result;
                      pid_t _pid{0};
                      istring _command;
                      istring _input_buf;
                      std::vector<istring> _args;
                      std::vector<istring> _envs;

                  }; // class iCommand


#elif defined(__WINDOWS__)
            // todo: Windows
#endif

		} // SPACE(process)
	} // SPACE(core)
} // SPACE(i)