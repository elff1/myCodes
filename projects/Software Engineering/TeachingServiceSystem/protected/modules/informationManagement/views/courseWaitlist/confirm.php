<?php
$this->breadcrumbs=array(
	InformationManagementModule::t('courseWaitlist','Course Waitlists')=>array('index'),
	InformationManagementModule::t('courseWaitlist','Course Confirm'),
);

$this->menu=array(
	array('label'=>InformationManagementModule::t('courseWaitlist','List CourseWaitlist'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Manage CourseWaitlist'), 'url'=>array('admin')),
);
Yii::app()->clientScript->registerCoreScript('jquery'); 
?>

<script type="text/javascript">

function pass(id,isyes)
{
	document.getElementById(id).innerHTML= "Processing...";
	$.ajax({
            type:"POST",
            dataType:"html",
            data:{"id":id,"pass":isyes,'<?php echo Yii::app()->request->csrfTokenName; ?>' : '<?php echo Yii::app()->request->getCsrfToken();?>'},
            url:"<?php echo Yii::app()->request->baseUrl;?>/index.php?r=informationManagement/courseWaitlist/Ajax",
            success:function(msg) {
                document.getElementById(id).innerHTML= msg;
				alert("SECCESS");
            }
        });
		
	//var url= "confirmAjax.php"+"?id="+id+"&pass="+isyes;

}


</script>
<h1><?php echo CHtml::encode(InformationManagementModule::t('courseWaitlist', 'Course Confirm')); ?></h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_confirm',
)); ?>


