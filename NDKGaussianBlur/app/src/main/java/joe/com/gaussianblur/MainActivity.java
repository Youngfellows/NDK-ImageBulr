package joe.com.gaussianblur;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import joe.com.blurlibrary.BlurCore;

public class MainActivity extends AppCompatActivity
        implements View.OnClickListener {
    ImageView img;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        img = (ImageView) findViewById(R.id.img);
        findViewById(R.id.btn_fastBlur).setOnClickListener(this);
        findViewById(R.id.btn_renderscript).setOnClickListener(this);
        findViewById(R.id.btn_openGl).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_fastBlur:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        long startTime = System.currentTimeMillis();
                        final Bitmap bp = BitmapFactory.decodeResource(getResources(), R.drawable.bp);
                        BlurCore.blurBitmap(bp, 25);
                        final long doTime = System.currentTimeMillis() - startTime;
                        img.post(new Runnable() {
                            @Override
                            public void run() {
                                img.setImageBitmap(bp);
                                String s = String.format("半径25，耗时：%d毫秒", doTime);
                                Toast.makeText(MainActivity.this, s, Toast.LENGTH_SHORT).show();
                            }
                        });
                    }
                }).start();
                break;
            case R.id.btn_renderscript:
                new Thread(new Runnable() {
                    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR1)
                    @Override
                    public void run() {
                        long startTime = System.currentTimeMillis();
                        Bitmap bp = BitmapFactory.decodeResource(getResources(), R.drawable.bp);
                        final Bitmap result = BlurCore.blurWithRenderScript(MainActivity.this, bp, 25);
                        final long doTime = System.currentTimeMillis() - startTime;
                        img.post(new Runnable() {
                            @Override
                            public void run() {
                                img.setImageBitmap(result);
                                String s = String.format("半径25，耗时：%d毫秒", doTime);
                                Toast.makeText(MainActivity.this, s, Toast.LENGTH_SHORT).show();
                            }
                        });
                    }
                }).start();
                break;
        }
    }
}
