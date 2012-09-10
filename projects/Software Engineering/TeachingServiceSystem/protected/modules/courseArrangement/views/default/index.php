<?php
$this->breadcrumbs=array(
	
	Yii::t('courseArrangement', $this->module->id),
);

Yii::app()->clientScript->registerCoreScript('jquery'); 

?>

<script type="text/javascript">

function getFile()
{

	
	$.ajax({
            type:"POST",
            dataType:"html",
            data:{'<?php echo Yii::app()->request->csrfTokenName; ?>' : '<?php echo Yii::app()->request->getCsrfToken();?>'},
			//data:{},
            url:"<?php echo Yii::app()->request->baseUrl;?>/index.php?r=courseArrangement/default/Ajax",
            success:function(msg) {
                //document.getElementById(id).innerHTML= msg;
				alert(msg);
            }
        });
}
function putFile()
{

	$.ajax({
            type:"POST",
            dataType:"html",
            data:{'<?php echo Yii::app()->request->csrfTokenName; ?>' : '<?php echo Yii::app()->request->getCsrfToken();?>'},
			//data:{},
            url:"<?php echo Yii::app()->request->baseUrl;?>/index.php?r=courseArrangement/default/Ajaxx",
            success:function(msg) {
                //document.getElementById(id).innerHTML= msg;
				alert(msg);
            }
        });
}

</script>

<h1><?php echo yii::t('courseArrangement', 'courseArrangement'); ?></h1>

<!--
<p>
This is the view content for action "<?php echo $this->action->id; ?>".
The action belongs to the controller "<?php echo get_class($this); ?>"
in the "<?php echo $this->module->id; ?>" module.
</p>
-->

<p>
<?php
 $filename="C:/myphp/root/red/TeachingServiceSystem/busy";
 $state=1;
 if(!file_exists($filename)){
	$state=1;
 }
 else{
	$state=0;
 }
 if($state==1){
	echo "<button type=\"button\" onclick=\"getFile();\">排课</button>";
	echo "<button type=\"button\" onclick=\"putFile();\">导入结果</button>";

	
 }
 else{
	echo "系统排课中，请稍后刷新页面";
 }
 ?>
<button  text='查看结果' onclick="window.location.href('/red/TeachingServiceSystem/index.php?r=courseArrangement/classtime')">查看结果</button>

</p>
