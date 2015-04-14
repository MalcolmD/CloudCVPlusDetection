#include <cloudcv.hpp>



#include <framework/marshal/marshal.hpp>
#include <framework/NanCheck.hpp>
#include "framework/Job.hpp"
#include "framework/ImageSource.hpp"
#include "modules/objectsDetect/objectsDetect.hpp"

#include <vector>

using namespace v8;
using namespace node;
using namespace cloudcv;


#include <framework/marshal/node_object_builder.hpp>
#include <framework/Logger.h>

namespace cloudcv
{
    class DetectObjectsTask : public Job
    {
    public:

        DetectObjectsTask(ImageSourcePtr image, NanCallback * callback)
            : Job(callback)
            , m_imageSource(image)
        {
            TRACE_FUNCTION;
        }

        virtual ~DetectObjectsTask()
        {
            TRACE_FUNCTION;
        }

    protected:

        // This function is executed in another thread at some point after it has been
        // scheduled. IT MUST NOT USE ANY V8 FUNCTIONALITY. Otherwise your extension
        // will crash randomly and you'll have a lot of fun debugging.
        // If you want to use parameters passed into the original call, you have to
        // convert them to PODs or some other fancy method.
        virtual void ExecuteNativeCode()
        {
            TRACE_FUNCTION;
            cv::Mat image = m_imageSource->getImage();

            if (image.empty())
            {
                SetErrorMessage("Cannot decode image");
                return;
            }

            if(!ProcessImage(image, m_detectResult))
             {
                SetErrorMessage("No detection captured");
                return;
             }

        }

        // This function is executed in the main V8/JavaScript thread. That means it's
        // safe to use V8 functions again. Don't forget the HandleScope!
        virtual Local<Value> CreateCallbackResult()
        {
            TRACE_FUNCTION;
            NanEscapableScope();
            return NanEscapeScope(MarshalFromNative(m_detectResult));
        }

    private:
        ImageSourcePtr m_imageSource;
        std::vector<cv::Rect>  m_detectResult;
    };

    NAN_METHOD(detectObjects)
    {
        TRACE_FUNCTION;
        NanEscapableScope();

        Local<Object> imageBuffer;
        std::string   imageFile;
        Local<Function> imageCallback;
        std::string     error;

        if (NanCheck(args)
            .Error(&error)
            .ArgumentsCount(2)
            .Argument(0).IsBuffer().Bind(imageBuffer)
            .Argument(1).IsFunction().Bind(imageCallback))
        {
            NanCallback *callback = new NanCallback(imageCallback);
            NanAsyncQueueWorker(new DetectObjectsTask(CreateImageSource(imageBuffer), callback));
            NanReturnUndefined();
        }
        else if (NanCheck(args)
            .Error(&error)
            .ArgumentsCount(2)
            .Argument(0).IsString().Bind(imageFile)
            .Argument(1).IsFunction().Bind(imageCallback))
        {
            NanCallback *callback = new NanCallback(imageCallback);
            NanAsyncQueueWorker(new DetectObjectsTask(CreateImageSource(imageFile), callback));
            NanReturnUndefined();
        }
        else if (!error.empty())
        {
            NanThrowTypeError(error.c_str());
        }

        NanReturnUndefined();
    }
}