package joe.com.blurlibrary;

import android.content.Context;
import android.graphics.Bitmap;
import android.os.Build;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.ScriptIntrinsicBlur;
import android.renderscript.Type;

import androidx.annotation.RequiresApi;

/**
 * Description
 * Created by chenqiao on 2016/4/8.
 */
public class BlurCore {

    public static native int blurBitmap(Bitmap bitmap, int radius);

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR1)
    public static Bitmap blurWithRenderScript(Context context, Bitmap bitmap, float radius) {
        if (radius > 25) {
            radius = 25;
        }
        RenderScript rs         = RenderScript.create(context);
        Allocation allocation = Allocation.createFromBitmap(rs, bitmap);
        Type       t          = allocation.getType();
        //Create allocation with the same type
        Allocation blurredAllocation = Allocation.createTyped(rs, t);
        //Create script
        ScriptIntrinsicBlur blurScript = ScriptIntrinsicBlur.create(rs, Element.U8_4(rs));
        //Set blur radius (maximum 25.0)
        blurScript.setRadius(radius);
        //Set input for script
        blurScript.setInput(allocation);
        //Call script for output allocation
        blurScript.forEach(blurredAllocation);
        //Copy script result into bitmap
        blurredAllocation.copyTo(bitmap);
        //Destroy everything to free memory
        allocation.destroy();
        blurredAllocation.destroy();
        blurScript.destroy();
        t.destroy();
        rs.destroy();
        return bitmap;
    }

    static {
        System.loadLibrary("blurcore");
    }
}
