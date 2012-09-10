<?php
//顶部的导航条
$this->breadcrumbs=array(
	InformationManagementModule::t('systemAdminBasicInfo','System Admin Basic Info')=>array('index'),
	InformationManagementModule::t('systemAdminBasicInfo','Batch Create Info'),
);


//右侧导航菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('systemAdminBasicInfo','List Basic Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('systemAdminBasicInfo','Manage Basic Info'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('systemAdminBasicInfo','Batch Create Info')); ?></h1>



<!--提交文件的表单-->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'systemAdminBasicInfo-batch-form-batchCreate-form',
	'enableAjaxValidation'=>false,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<!--提示信息-->
	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<!--提示信息-->
	<p class="note"><?php echo CHtml::encode(InformationManagementModule::t('other','Input format: csv, UTF-8 encoded, with format "systemAdmin_id, current_grade, program_id, entry_date, class_id, remark, first_name, last_name, sex, photo, date_of_birth, ethnic_group, political_status, birth_place_city, birth_place_province, original_residence_city, original_residence_province, home_address, home_postcode, home_phone, email, phone, identity_card_number" per line (introduction can have multiple lines, by enclosing it in double quotes), leading & trailing whitespace ignored.')); ?></p>
	
	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'file'); ?>
		<?php echo $form->fileField($model,'file'); ?>
		<?php echo $form->error($model,'file'); ?>
	</div>


	<!--提交按钮-->
	<div class="row buttons">
		<?php echo CHtml::submitButton(InformationManagementModule::t('other','Submit')); 
		 ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->