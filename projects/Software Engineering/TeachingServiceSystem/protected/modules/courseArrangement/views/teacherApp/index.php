<?php
$this->breadcrumbs=array(
	'Teacher Apps',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'New application'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Quary application'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Confirm application'), 'url'=>array('confirm')),
);
Yii::app()->clientScript->registerCoreScript('jquery'); 
?>



<script type="text/javascript">
function appDelete(id)
{

	$.ajax({
            type:"POST",
            dataType:"html",
            data:{"id":id,'<?php echo Yii::app()->request->csrfTokenName; ?>' : '<?php echo Yii::app()->request->getCsrfToken();?>'},
            url:"<?php echo Yii::app()->request->baseUrl;?>/index.php?r=courseArrangement/teacherApp/AjaxDelete",
            success:function(msg) {
                document.getElementById(id).innerHTML="<b>ID:"+id+"<br /> 已经撤销</b>";
				alert("撤销成功");
            }
        });
		
	//var url= "confirmAjax.php"+"?id="+id+"&pass="+isyes;

}

function appUpdate(id)
{
	
	alert("SECCESS");


}
</script>



<h1>Teacher Apps</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>


